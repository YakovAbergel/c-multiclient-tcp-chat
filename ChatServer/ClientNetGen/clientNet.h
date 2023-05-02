#ifndef __CLIENTNET_H__
#define __CLIENTNET_H__


#define MIN_PORT 1
#define MAX_PORT 64000

typedef struct ClientNet ClientNet;

typedef enum ClientNet_Result 
{
	CLIENT_SUCCESSS = 0,
	CLIENT_UNINITIALIZED_ERROR,
	CLIENT_SOCKET_ERROR,
	CLIENT_CONNECT_ERROR,
	CLIENT_RECV_ERROR,
	CLIENT_SEND_ERROR

}ClientNet_Result;
	


ClientNet* ClientCreate(char *_address, int _port);

void ClientDestroy(ClientNet **_client);

ClientNet_Result ConnectionWithTheServer(ClientNet *_client); 

ClientNet_Result SendTo(ClientNet *_client, char *_messageToSend, size_t _lengthMsg); 

ClientNet_Result Recvfrom(ClientNet *_client, char *_buffer, size_t _bufferSize); 


#endif /* __CLIENTNET_H__ */
