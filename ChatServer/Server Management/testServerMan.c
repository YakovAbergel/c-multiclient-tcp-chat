#include "serverManagement.h"
#include "../ServerNetGen/serverNetGen.h"
#include <stdio.h>



int main()
{
	ChatServer* chatServer;
    Server_Result res;
	chatServer = ChatServerCreate();
	res = RunChatServer(chatServer);
	printf("res = %d",res);
	/*ServerDestroy(server);*/
	return 0;
}