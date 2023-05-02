#include "serverNetGen.h"
#include <stdio.h>
#include <string.h>

#define MAX_SIZE_DATA 4096

static int GM(const int _clientSock, void* _msg, size_t _readByts, void *_appServer);


int main()
{
	Server* server;
	Server_Result res;

	server = InitServer(2345, 500, 1000, NULL, NULL, GM, NULL, NULL);


	res = RanServer(server);
	printf("res = %d",res);
	/*ServerDestroy(server);*/
	return 0;
}

static int GM(int _clientSock, void *_msg, size_t _msgSize, void *_appServer)
{
	char msg[] = "i am client";
	ServerSendMsg(_clientSock, (void*)msg, strlen(msg));
	printf("%s\n", (char*)msg);
}


