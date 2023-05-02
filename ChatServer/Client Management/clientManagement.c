#include <stdio.h> /*print, scan*/ 
#include <stdlib.h> /*malloc, free*/
#include <string.h> /*strcpy, strlen*/
#include <sys/select.h> /*select*/
#include "UI.h"
#include "ChatOpen.h"
#include "../../GenericDataStructures+DynamicLibrary/ListGen/listGen.h"   
#include "../../GenericDataStructures+DynamicLibrary/ListItr/listItr.h"  
#include "../../GenericDataStructures+DynamicLibrary/ListFunc/listFunc.h" 
#include "../ClientNetGen/clientNet.h"
#include "clientManagment.h"
#include "../Protocol/protocol.h"
#include "../../GenericDataStructures+DynamicLibrary/VectorGen/vectorGen.h" 
#include <signal.h>

#define MAX_GROUP_NUM 50
#define BLOCK_SIZE (MAX_GROUP_NUM/10)
#define PORT 2345
#define PACK_SIZE 256
#define FAIL 0
#define SUCCESS 1
#define MAX_NAME_LENGTH 20
#define MAX_PAS_LEN 10
#define ADDRESS "127.0.0.1"
#define REGISTRATION 1
#define LOG_IN 2
#define CREATE_GROUP 1
#define JOIN_GROUP 2
#define LEAVE_GROUP 3
#define LOG_OUT 4
#define EXIT 3

typedef struct GroupDetails
{
	int m_receverPid;
	int m_senderPid;
	char* m_nameGroups;
} GroupDetails;

struct ClientMan 
{
	ClientNet *m_clientNet;
	List *m_groupDetails;
	char *m_clientName;	
};

static ClientMan_Result FindingProtocolFuncByTag(Tag_Protocol _tag, char* _recvPackBuff, char* _ip, char* _port, int* _status);
static ClientMan_Result FindingProtocolFuncByStatusOpeningScreen(int *status, char* _sendPackBuff, int* _replyMsgSize,
										 char* _userName, char* _password);
static ClientMan_Result FindingProtocolFuncByStatusAfterLogin(ClientMan *_client, int status, char* _sendPackBuff, int* _replyMsgSize,
										 char* _userName, char* _groupName);
static void UiFunc (char* _username, char* _password, int* _status);
static ClientMan_Result UserOpeningScreen(ClientMan *_client, char* _buffer, char* _username, char* _password, int* _status, int* _replyMsgSize,
											   Tag_Protocol* _tag);
static ClientMan_Result ScreenAfterLogin(ClientMan *_client, char* _buffer, char* _userName, char* _groupName, int* _status, int* _replyMsgSize,
 												Tag_Protocol* _tag, char* _ip, char* _port);
static ClientMan_Result ShowAllExistingGroups(ClientMan *_client, Vector* _vec, char* _buffVec, int* _index);
static void RemoveGroupDetailsfromList(List* _client, char* _groupName);
void ListPrint(List* _groupDetails);
static void DestroyGroupDetails(void *_item);


ClientMan* ClientManageCreate(char* _clientName) 
{
	ClientMan *client;
	char* name;
	if (_clientName == NULL || strlen (_clientName) > MAX_NAME_LENGTH)
	{
		return NULL;
	}
	if ((client = (ClientMan*) malloc (sizeof(ClientMan))) == NULL)
	{
		return NULL;
	}

	if ((client ->m_groupDetails = ListCreate ()) == NULL)
	{
		free (client);
		return NULL;
	}

	if ((client -> m_clientName = (char*) malloc (sizeof (char)* MAX_NAME_LENGTH)) == NULL)
	{
		ListDestroy (&client -> m_groupDetails, NULL);
		free (client);
		return NULL;
	}
	if ((client -> m_clientNet = ClientCreate (ADDRESS, PORT)) == NULL)
	{
		ListDestroy (&client -> m_groupDetails, NULL);
		free (client -> m_clientName);
		free (client);
		return NULL;
	}
	strcpy (client -> m_clientName, _clientName);
	client -> m_clientName[strlen(_clientName)] = '\0';
	return client;
}

void ClientManDestroy(ClientMan** _clientMan)
{
	if(_clientMan != NULL && *_clientMan != NULL)
	{	
		ClientDestroy(&((*_clientMan)->m_clientNet));
		ListDestroy(&((*_clientMan)->m_groupDetails), DestroyGroupDetails);
		free((*_clientMan)->m_clientName);
		free(*_clientMan);
		*(_clientMan) = NULL;
	}
} 


ClientMan_Result Client_Run(ClientMan *_client) 
{
	int openingScreen = 0, statusAfterLogin = 0, replyMsgSize, flag = 0, exit = 0;
	Tag_Protocol tag;
	ClientMan_Result res1, res2;
	char userName[MAX_NAME_LENGTH] = {0};
	char groupName[MAX_NAME_LENGTH] = {0};
	char password[MAX_PAS_LEN] = {0};
	char ip[MAX_NAME_LENGTH] = {0};
	char port[MAX_NAME_LENGTH] = {0};
	char buffer[PACK_SIZE] = {0};
	
	if ((ConnectionWithTheServer (_client->m_clientNet)) != CLIENT_SUCCESSS)
	{
		return CLIET_MANAGE_CONNECT_ERROR;
	}
	
	while (1)
	{
		if(flag == 0)
		{
			res1 = UserOpeningScreen(_client,buffer,userName,password,&openingScreen,&replyMsgSize,&tag);
			if(openingScreen == EXIT)
			{
				break;
			}
			if(openingScreen == LOG_IN && res1 == CLIET_MANAGE_SUCCESS)
			{
				flag = 1;
			}
		}
		else
		{
			res2 = ScreenAfterLogin(_client,buffer,userName,groupName,&statusAfterLogin,&replyMsgSize,&tag,ip,port);
			if(statusAfterLogin == LOG_OUT && res2 == CLIET_MANAGE_SUCCESS)
			{
				flag = 0;
			}
		}
	}
	ClientDestroy(&_client->m_clientNet); 
	
	return CLIET_MANAGE_SUCCESS;
}

static ClientMan_Result UserOpeningScreen(ClientMan *_client, char* _buffer, char* _username, char* _password, int* _status, int* _replyMsgSize,
											   Tag_Protocol* _tag)
{
	int statusProtocol;
	ClientMan_Result res;

	UI_OpeningScreen(_username, _password,_status);
	
	if(FindingProtocolFuncByStatusOpeningScreen(_status, _buffer, _replyMsgSize, _username, _password) != CLIET_MANAGE_SUCCESS)
	{
		return CLINT_MAN_PROTOCOL_ERROR;
	}

	if(*_status == EXIT)
	{
		return CLIET_MANAGE_SUCCESS;
	}

	if((SendTo(_client->m_clientNet, _buffer, strlen (_buffer))) != CLIENT_SUCCESSS)
	{
		return CLIET_MANAGE_SEND_ERROR;
	}
		
	if((Recvfrom(_client->m_clientNet, _buffer, PACK_SIZE)) != CLIENT_SUCCESSS)
	{
		return CLIET_MANAGE_RECIEVE_ERROR;
	}

	*_tag = ProtocolGetTag(_buffer);
	if((res = FindingProtocolFuncByTag(*_tag, _buffer,NULL,NULL,&statusProtocol)) != CLIET_MANAGE_SUCCESS)
	{
		return CLINT_MAN_PROTOCOL_ERROR;
	}

	return CLIET_MANAGE_SUCCESS;
}

static ClientMan_Result ScreenAfterLogin(ClientMan *_client, char* _buffer, char* _userName, char* _groupName, int* _status, int* _replyMsgSize,
 												Tag_Protocol* _tag, char* _ip, char* _port)
{
	int statusProtocol;
	ClientMan_Result res;
	GroupDetails* groupDetails = NULL;

	UI_ScreenAfterLogin (_groupName,_status);
	if(FindingProtocolFuncByStatusAfterLogin(_client, *_status, _buffer, _replyMsgSize, _userName, _groupName) != CLIET_MANAGE_SUCCESS)
	{
		return CLINT_MAN_PROTOCOL_ERROR;
	}

	if((SendTo(_client->m_clientNet, _buffer, strlen (_buffer))) != CLIENT_SUCCESSS)
	{
		return CLIET_MANAGE_SEND_ERROR;
	}
		
	if((Recvfrom(_client->m_clientNet, _buffer, PACK_SIZE)) != CLIENT_SUCCESSS)
	{
		return CLIET_MANAGE_RECIEVE_ERROR;
	}

	*_tag = ProtocolGetTag(_buffer);
	if((res = FindingProtocolFuncByTag(*_tag, _buffer, _ip, _port, &statusProtocol)) != CLIET_MANAGE_SUCCESS)
	{
		return CLINT_MAN_PROTOCOL_ERROR;
	}

	if(*_tag == TAG_JOIN_GROUP_REPLY || *_tag == TAG_CREAT_GROUP_REPLY)
	{
		if((groupDetails = (GroupDetails*)malloc(sizeof(GroupDetails))) == NULL)
		{
			return CLIET_MANAGE_ALLOCATION_ERROR;
		}
		OpenChat(_ip, _port, _userName, _groupName, &groupDetails->m_receverPid, &groupDetails->m_senderPid);
		groupDetails->m_nameGroups = _groupName;
		ListPushHead(_client->m_groupDetails, (void*)groupDetails);
	}
	else if(*_tag == TAG_LEAVE_GROUP_REPLY)
	{
		RemoveGroupDetailsfromList(_client->m_groupDetails, _groupName);
	}
	else if(*_tag == TAG_LOG_OUT_REPLY)
	{
		ListDestroy(&_client->m_groupDetails, DestroyGroupDetails);
	}
	return CLIET_MANAGE_SUCCESS;
}

static void RemoveGroupDetailsfromList(List* _groupD, char* _groupName)
{
	ListItr begin = ListItrBegin(_groupD);
	ListItr end = ListItrEnd(_groupD);
	GroupDetails* groupDetails = NULL;
	while(begin != end)
	{
		groupDetails = (GroupDetails*)ListItrGet(begin);
		if(groupDetails->m_nameGroups == _groupName)
		{
			kill(groupDetails->m_receverPid,SIGKILL);
			kill(groupDetails->m_senderPid,SIGKILL);
			ListItrRemove(begin);
			break;
		}
		begin = ListItrNext(begin);
	}
}

static ClientMan_Result FindingProtocolFuncByStatusOpeningScreen(int* _status, char* _sendPackBuff, int* _replyMsgSize,
										 char* _userName, char* _password)
{
	switch (*_status)
	{
		case FAIL:
			printf("Error: Invalid selection\n");
			return CLIENT_MAN_INVALID_SELECTION;
			break;

		case REGISTRATION:
			if((*_replyMsgSize = ProtocolRegRequestPack(_sendPackBuff, _userName,  _password)) == 0)
			{
				return CLIENT_POINTER_NOT_INIT_ERR;
			}
			break;
			
		case LOG_IN:
			if((*_replyMsgSize = ProtocolLogRequestPack(_sendPackBuff, _userName, _password)) == 0)
			{
				return CLIENT_POINTER_NOT_INIT_ERR;
			}
			break;

		case EXIT:
				*_status = EXIT;
			break;
	}
	return CLIET_MANAGE_SUCCESS;
}

static ClientMan_Result FindingProtocolFuncByStatusAfterLogin(ClientMan *_client, int status, char* _sendPackBuff, int* _replyMsgSize,
										 char* _userName, char* _groupName)
{
	char buffVec[PACK_SIZE];
	Vector* vec;
	int index;
	size_t i;
	char* groupNameVec;

	switch (status)
	{
		case FAIL:
			printf("Error: Invalid selection\n");
			return CLIENT_MAN_INVALID_SELECTION;
			break;

		case CREATE_GROUP:
			if((*_replyMsgSize = ProtocolCreateGroupRequestPack(_sendPackBuff,_groupName,_userName)) == 0)
			{
				return CLIENT_POINTER_NOT_INIT_ERR;
			}
			break;

		case JOIN_GROUP:
			if(ShowAllExistingGroups(_client, vec, buffVec, &index) == CLIET_MANAGE_SUCCESS)
			{
				VectorGet(vec, index-1, (void**)groupNameVec);
				if((*_replyMsgSize = ProtocolJoinGroupRequestPack(_sendPackBuff,groupNameVec,_userName)) == 0)
				{
					return CLIENT_POINTER_NOT_INIT_ERR;
				}
			}
			else
			{
				printf("There are no groups!\n");
				return CLIENT_MAN_VECTOR_SIZE_ERR;
			}

			break;

		case LEAVE_GROUP:
		printf("\nThese are the groups you are registered to, which group would you like to leave?\n");
			ListPrint(_client->m_groupDetails);
			scanf("%s",_groupName);
			if((*_replyMsgSize = ProtocolLeaveGroupRequestPack(_sendPackBuff,_groupName,_userName)) == 0)
			{
				return CLIENT_POINTER_NOT_INIT_ERR;
			}
			break;

		case LOG_OUT:
			if((*_replyMsgSize = ProtocolLogOutRequestPack(_sendPackBuff,_userName)) == 0)
			{
				return CLIENT_POINTER_NOT_INIT_ERR;
			}
			break;
	}
	return CLIET_MANAGE_SUCCESS;
}

static ClientMan_Result ShowAllExistingGroups(ClientMan *_client, Vector* _vec, char* _buffVec, int* _index)
{
	int res1, res2, status;
	if((_vec = VectorCreate(MAX_GROUP_NUM, BLOCK_SIZE)) == NULL)
	{
		return CLIENT_MAN_VECTOR_CREATE_ERR;
	}

	if((res1 = ProtocolShowAllExistingGroupsRequestPack(_buffVec)) == 0)
	{
		CLINT_MAN_PROTOCOL_ERROR;
	}

	if((SendTo(_client->m_clientNet, _buffVec, strlen (_buffVec))) != CLIENT_SUCCESSS)
	{
		return CLIET_MANAGE_SEND_ERROR;
	}
		
	if((Recvfrom(_client->m_clientNet, _buffVec, PACK_SIZE)) != CLIENT_SUCCESSS)
	{
		return CLIET_MANAGE_RECIEVE_ERROR;
	}

	res2 = ProtocolShowAllExistingGroupsReplyUnPack(_buffVec, _vec);
	if(res2 == 0)
	{
		return CLINT_MAN_PROTOCOL_ERROR;
	}

	if(VectorSize(_vec) == 0)
	{
		return CLIENT_MAN_VECTOR_SIZE_ERR;
	}
	UI_ShowAllExistingGroups(_vec, _index);
	return CLIET_MANAGE_SUCCESS;
}

static ClientMan_Result FindingProtocolFuncByTag(Tag_Protocol _tag, char* _recvPackBuff, char* _ip, char* _port, int* _status)
{
	
	switch (_tag)
	{
		case TAG_REGESTRESTION_REPLY:
			if(ProtocolRegReplyUnPack(_recvPackBuff, _status) == 0)
			{
				return CLIET_MANAGE_REGISTRETION_ERROR;
			}
			if(*_status == 0)
			{
				printf("Registration failed!\n");
				return CLIET_MANAGE_REGISTRETION_ERROR;
			}
			else
			{
				printf("Registration was successful!\n");
			}
			break;

		case TAG_LOG_IN_REPLY:
			if ((ProtocolLogReplyUnPack(_recvPackBuff, _status)) == 0)
			{
				return CLIET_MANAGE_LOGIN_ERROR;
			}
			if(*_status == 0)
			{
				printf("Login failed!\n");
				return CLIET_MANAGE_LOGIN_ERROR;
			}
			else
			{
				printf("The login was successful!\n");
			}
			break;

		case TAG_CREAT_GROUP_REPLY:
			if((ProtocolCreateGroupReplyUnPack(_recvPackBuff, _ip, _port, _status)) == 0)
			{
				return CLIET_MANAGE_CREATE_GROUP_ERROR;
			}
			if(*_status == 0)
			{
				printf("Create group failed!\n");
				return CLIET_MANAGE_CREATE_GROUP_ERROR;
			}
			else
			{
				printf("Group creation was successful!\n");
			}
			break;

		case TAG_JOIN_GROUP_REPLY:
			if((ProtocolJoinGroupReplyUnPack(_recvPackBuff, _ip, _port, _status)) == 0)
			{
				return CLIET_MANAGE_CREATE_GROUP_ERROR;
			}
			if(*_status == 0)
			{
				printf("Join group failed!\n");
				return CLIET_MANAGE_CREATE_GROUP_ERROR;
			}
			else
			{
				printf("Join group was successful!\n");
			}
			break;

			case TAG_LEAVE_GROUP_REPLY:
			if((ProtocolLeaveGroupReplyUnPack(_recvPackBuff, _status)) == 0)
			{
				return CLIET_MANAGE_CREATE_GROUP_ERROR;
			}
			if(*_status == 0)
			{
				printf("Leave group failed!\n");
				return CLIET_MANAGE_CREATE_GROUP_ERROR;
			}
			else
			{
				printf("Leave group was successful!\n");
			}
			break;

		case TAG_LOG_OUT_REPLY:
			if((ProtocolLogOutReplyUnPack(_recvPackBuff, _status)) == 0)
			{
				return CLIET_MANAGE_CREATE_GROUP_ERROR;
			}
			if(*_status == 0)
			{
				printf("Logout failed!\n");
				return CLIET_MANAGE_CREATE_GROUP_ERROR;

			}
			else
			{
				printf("Logout was successful!\n");
			}
			break;
	}
	return CLIET_MANAGE_SUCCESS;
}

void ListPrint(List* _groupDetails)
{
    ListItr begin = ListItrBegin(_groupDetails);
	ListItr end = ListItrEnd(_groupDetails);
	GroupDetails* groupDetails = NULL;

    while (begin != end)
    {
		groupDetails = (GroupDetails*)ListItrGet(begin);
        printf("(%s)   ", ((char*)groupDetails->m_nameGroups));
        begin = ListItrNext(begin);
    }
    putchar('\n');
}

static void DestroyGroupDetails(void *_item)
{
	kill(((GroupDetails*)(_item))->m_receverPid,SIGKILL);
	kill(((GroupDetails*)(_item))->m_senderPid,SIGKILL);
	/*free(((GroupDetails*)(_item))->m_nameGroups);*/
	free(_item);
}


