#include <stdio.h> /* printf */
#include <stdlib.h> /*malloc, calloc*/
#include <string.h> /* memset, strlen */
#include <sys/types.h> /* sockaddr */
#include <sys/socket.h> /* socket, sendto, recvfrom */
#include <netinet/in.h> /* sockaddr_in */

#include "clientNet.h"

struct ClientNet 
{
	int   m_sock;
	int   m_port;
	char *m_address;
};

static void initAddress(ClientNet *_client, struct sockaddr_in *_sin);

ClientNet* ClientCreate(char *_address, int _port) 
{
	ClientNet *client = NULL;
	size_t length = 0;
	
	if (NULL == _address || MIN_PORT > _port || _port > MAX_PORT) 
    {
		return NULL;
	}
	
	client = (ClientNet*)malloc(sizeof(ClientNet));
	if (NULL == client) 
    {
		return NULL;
	}
	
	length = strlen(_address) + 1;
	client->m_address = (char*)malloc(sizeof(char) * length);
	if (NULL == client->m_address) 
    {
		free(client);
		return NULL;
	}
	client->m_port = _port;
	strcpy(client->m_address, _address);
	client->m_sock = 0;
	return client;
}

void ClientDestroy(ClientNet **_client) 
{
	if (NULL == _client || NULL == *_client) 
    {
		return;
	}
	close((*_client)->m_sock);
	free(*_client);
	*_client = NULL;
}

ClientNet_Result ConnectionWithTheServer(ClientNet *_client) 
{
 	struct sockaddr_in sin;
    int length = sizeof(sin); 

 	if (NULL == _client) 
    {
 		return CLIENT_UNINITIALIZED_ERROR;
 	}
 	
	_client->m_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (_client->m_sock < 0) 
    {
		return CLIENT_SOCKET_ERROR;
	}

    initAddress(_client, &sin);

	if (connect(_client->m_sock, (struct sockaddr*)&sin, length) < 0) 
    {
    	close(_client->m_sock);
		return CLIENT_CONNECT_ERROR;
	} 
	return CLIENT_SUCCESSS;
}

ClientNet_Result SendTo(ClientNet *_client, char *_messageToSend, size_t _lengthMsg) 
{
    int sendBytes;

	if (NULL == _client|| NULL == _messageToSend || _lengthMsg <= 0 ) 
    {
 		return CLIENT_UNINITIALIZED_ERROR;
 	}

	sendBytes = send(_client->m_sock, _messageToSend, _lengthMsg, 0);
    if (sendBytes != _lengthMsg) 
	{
		perror("sendto failed");
		return CLIENT_SEND_ERROR;
	}

	return CLIENT_SUCCESSS;   
} 

ClientNet_Result Recvfrom(ClientNet *_client, char *_buffer, size_t _bufferSize) 
{
  size_t readBytes = 0; 

	if (NULL == _client|| NULL == _buffer) 
    {
 		return CLIENT_UNINITIALIZED_ERROR;
 	}

 	readBytes = recv(_client->m_sock, _buffer, _bufferSize ,0); 

	if (readBytes == 0) 
    {
		return CLIENT_RECV_ERROR;		
	}
	else if(readBytes < 0)
	{
		perror("Recvfrom failed");
		return CLIENT_RECV_ERROR;
	}	

    _buffer[readBytes] = '\0';
	return CLIENT_SUCCESSS;
}





static void initAddress(ClientNet *_client, struct sockaddr_in *_sin) 
{
	memset(_sin, 0, sizeof(*_sin));	
	_sin->sin_family = AF_INET;
	_sin->sin_addr.s_addr = inet_addr(_client->m_address);
	_sin->sin_port = htons(_client->m_port);
}
