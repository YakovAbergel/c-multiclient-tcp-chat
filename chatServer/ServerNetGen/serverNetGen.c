#include "serverNetGen.h"
#include "../../GenericDataStructures+DynamicLibrary/ListGen/listGen.h"
#include "../../GenericDataStructures+DynamicLibrary/ListItr/listItr.h"
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/select.h>


#define FALSE 1
#define TRUE 0
#define SIZE_OF_BUFF 4096

struct Server
{
	List* m_clientList;
	int m_numOfClient;
	int m_maxNumOfClient;
	int m_listeningSock;
	fd_set m_master;
	fd_set m_working;
	int m_flagStopRun;
	NewClient m_newClient;
	CloseClient m_closeClient;
	GotMessage m_gotMsg;
	Fail m_fail;
	void* m_appServer;
};

static Server_Result CheckNewClients(Server* _server);
static Server_Result CheckCurrClients(Server* _server, int client_sock);
static Server_Result CheckListClients(Server* _server, int _activity);
static void FreeClient(void* _item);


Server* InitServer(size_t _port, size_t _sizeBacklog, size_t _maxNumOfClient,
 					NewClient _newClient, CloseClient _closeClient, GotMessage _gotMsg, Fail _fail, void* _appServer)
{
	Server* server = NULL;
	int optval = 1;
	struct sockaddr_in sin;

	if(_port < MIN_NUM_OF_PORT || _port > MAX_NUM_OF_PORT || _sizeBacklog == 0 
	   || _maxNumOfClient > MAX_NUM_OF_CLIENT || _maxNumOfClient == 0 || _gotMsg == NULL)
	{
		return NULL;
	}

	if((server = (Server*)malloc(sizeof(Server))) == NULL)
	{
		return NULL;
	}

	if((server->m_listeningSock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket() failed");
		/*close(server->m_listeningSock);*/
		free(server);
		return NULL;
	}

	if(setsockopt(server->m_listeningSock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) 
	{
		perror("reuse failed");
		close(server->m_listeningSock);
		free(server);
		return NULL;
	}
	
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(_port);
	if (bind(server->m_listeningSock, (struct sockaddr *) &sin, sizeof(sin)) < 0)
	{
		perror("bind failed");
		close(server->m_listeningSock);
		free(server);
		return NULL;
	}
	
	if (listen(server->m_listeningSock, _sizeBacklog) < 0)
	{
		perror("listen failed");
		close(server->m_listeningSock);
		free(server);
		return NULL;
	}

	if((server->m_clientList = ListCreate()) == NULL)
	{
		close(server->m_listeningSock);
		free(server);
		return NULL;
	}

	server->m_maxNumOfClient = _maxNumOfClient;
	server->m_numOfClient = 0;
	server->m_flagStopRun = FALSE;
	server->m_newClient = _newClient;
	server->m_closeClient = _closeClient;
	server->m_gotMsg = _gotMsg;
	server->m_fail = _fail;
	server->m_appServer = _appServer;
	FD_ZERO(&server->m_master);
   	FD_SET(server->m_listeningSock, &server->m_master);

	return server;
}

void ServerDestroy(Server** _server)
{
	if(_server != NULL && *_server != NULL)
	{	
		ListDestroy(&((*_server)->m_clientList), FreeClient);
		close((*_server)->m_listeningSock);
		free(*_server);
		*(_server) = NULL;
	}
}

Server_Result RanServer(Server* _server)
{
	int activity;
	Server_Result res;

	if(_server == NULL)
	{
		return SERVER_UNINITIALIZED_ERROR;
	}

	while(_server->m_flagStopRun)
	{
		_server->m_working = _server->m_master;
		activity = select(1024, &_server->m_working, NULL, NULL, NULL);
		if((activity < 0))
		{
			perror("select error");
			if(_server->m_fail != NULL)
			{
				_server->m_fail(SERVER_SELECT_ERROR);
				if(_server->m_flagStopRun == TRUE)
				{
					break;
				}
			}
			/*else
			{
				return SERVER_SELECT_ERROR;
			}*/
		}
		if(FD_ISSET(_server->m_listeningSock, &_server->m_working))
		{
			if((res = CheckNewClients(_server)) != SERVER_SUCCESS)
			{
				if(_server->m_fail != NULL)
				{
					_server->m_fail(res);
					if(_server->m_flagStopRun == TRUE)
					{
						break;
					}
				}
				/*else if(res == SERVER_ACCEPT_ERROR || res == SERVER_ALLOCATION_FAILED || res == SERVER_LIST_PUSH_ERROER)
				{
					return res;
				}*/
			}
			--activity;
		}
		if(activity > 0)
		{
			if((res = CheckListClients(_server,activity)) != SERVER_SUCCESS)
			{
				if(res == SERVER_STOP_RUN)
				{
					break;
				}
				if(_server->m_fail != NULL)
				{
					_server->m_fail(res);
					if(_server->m_flagStopRun == TRUE)
					{
						break;
					}
				}
				/*else if(res == SERVER_LIST_ITR_ERROR)
				{
					return res;
				}*/
			}
		}
	}
	
	return SERVER_STOP_RUN;
}

Server_Result ServerSendMsg(int _clientSock, void* _data, int _sizeData)
{
	int sent_byts;

	if(_data == NULL) 
	{
		return SERVER_POINTER_NOT_INITIALIZED_ERROR;
	}

	if(_clientSock < 1 || _clientSock > MAX_NUM_OF_CLIENT || _sizeData < 1)
	{
		return SERVER_INPUT_ERROR;
	}

	sent_byts = send(_clientSock, _data, _sizeData,0);
	if(sent_byts != _sizeData)
	{
		perror("send failed");
		return SERVER_SEND_ERROR;
	}

	return SERVER_SUCCESS;
}

size_t StopRun(Server* _server)
{
	if(_server == NULL)
	{
		return 0;
	}
	_server->m_flagStopRun = TRUE;
	
	return _server->m_numOfClient;
}

static Server_Result CheckNewClients(Server* _server)
{
	struct sockaddr_in client_sin;
	socklen_t addr_len = sizeof(client_sin);
	int* client_sock = (int*)malloc(sizeof(int)); 

	if(client_sock == NULL)
	{
		return SERVER_ALLOCATION_FAILED;
	}

	*client_sock = accept(_server->m_listeningSock, (struct sockaddr *) &client_sin, &addr_len);

	if(_server->m_numOfClient == _server->m_maxNumOfClient)
	{
		close(*client_sock);
		free(client_sock);
		return SERVER_LIST_SIZE_ERROR;
	}

	if (*client_sock < 0)
	{
		free(client_sock);
		return SERVER_ACCEPT_ERROR;
	}

	if(_server->m_newClient != NULL)
	{
		if(!(_server->m_newClient(*client_sock)))
		{
			close(*client_sock);
			free(client_sock);
			return SERVER_SUCCESS;
		}
	}

	FD_SET(*client_sock, &_server->m_master);
	if(ListPushHead(_server->m_clientList, client_sock) != LIST_SUCCESS)
	{
		close(*client_sock);
		free(client_sock);
		return SERVER_LIST_PUSH_ERROER;
	}
	++(_server->m_numOfClient);

	return SERVER_SUCCESS;
}

static Server_Result CheckListClients(Server* _server, int _activity)
{
	ListItr begin, end;
	int* client_sock = NULL;
	Server_Result res;

	if((begin = ListItrBegin(_server->m_clientList)) == NULL || (end = ListItrEnd(_server->m_clientList)) == NULL)
	{
		return SERVER_LIST_ITR_ERROR;
	}

	while(!ListItrEquals(begin, end) && _activity > 0)
	{
		client_sock = (int*)(ListItrGet(begin));
		begin = ListItrNext(begin);

		if(FD_ISSET(*client_sock, &_server->m_working))
		{
			if((res = CheckCurrClients(_server, *client_sock)) != SERVER_SUCCESS)
			{
				FD_CLR(*client_sock, &_server->m_master);
				close(*client_sock);
				free(client_sock);
				ListItrRemove(ListItrPrev(begin));
				--(_server->m_numOfClient);

				if(_server->m_closeClient != NULL)
				{
					_server->m_closeClient(*client_sock);
				}

				if(res == SERVER_RECIEVED_ERROR && _server->m_fail != NULL)
				{
					_server->m_fail(res);
					if(_server->m_flagStopRun == TRUE)
					{
						return SERVER_STOP_RUN;
					}
				}
			}
			--_activity;
		}
	}
	
	return SERVER_SUCCESS;
}

static Server_Result CheckCurrClients(Server* _server, int client_sock)
{
    /*void* buff;
    int buffLen = SIZE_OF_BUFF;*/
    char buff[4096];
    int expected_data_len = sizeof(buff);
	int read_bytes, sent_bytes;
	/*char newData[4096];
	char data[] = " - data from server to client";*/

	read_bytes = recv(client_sock, buff, expected_data_len, 0);
	
	if (read_bytes == 0)
	{
		return SERVER_CONNECTION_IS_CLOSED_SUCCESS;
	}

	else if (read_bytes < 0) 
	{ 
		perror("client_sock recv failed");
		return SERVER_RECIEVED_ERROR;
	}
	else
	{
		buff[expected_data_len] = '\0';
		_server->m_gotMsg(client_sock, buff, read_bytes, _server->m_appServer);

		/*printf("%s\n", buff);
		sprintf(newData , "%d" , client_sock) ;
		strcat(newData, data);
		sent_bytes = send(client_sock, newData, strlen(newData), 0);
		if(sent_bytes != strlen(newData)) 
		{
			perror("send failed");
			return SERVER_SEND_ERROR;
		}*/
	}

	return SERVER_SUCCESS;
}

static void FreeClient(void* _item)
{
	if((*(int*)_item) > 0)
	{
		close((*(int*)_item));
		free(_item);
	}
}
