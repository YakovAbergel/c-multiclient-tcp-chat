#include <stdio.h>
#include <string.h>
#include "clientNet.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define RESET   "\x1b[0m"
#define BUFFER 4096

void ClientCreateTEST() 
{
	ClientNet *client = NULL;
	int port = 2345;
	char address[] = "127.0.0.1";

    char clientName[100] = " Benny you are amaizing";

	client = ClientCreate(address, port);
	if (NULL == client) 
    {
       printf(RED"\n Client Create NOT Works Well \n"RESET);
	}
    else
    {
		printf(GREEN"\n Client Create Works Well \n"RESET);
    }
}

void ClientDestroyTEST() 
{
	ClientNet *client = NULL;
	int port = 2345;
	char address[] = "127.0.0.1";

	char clientName[100] = " Benny you are amaizing";

	client = ClientCreate(address,port);
	ClientDestroy(&client);
	ClientDestroy(&client);
    
    printf(GREEN"\n Client Destroy Works Well \n"RESET);
}

int ClientConnectTEST() 
{
	ClientNet *client = NULL;
	ClientNet_Result status;
	int port = 2345;
	char address[] = "127.0.0.1";

    char clientName[100] = " Benny you are amaizing";

	client = ClientCreate(address, port);

    if(CLIENT_SUCCESSS == ConnectionWithTheServer(client))
    {
        printf(GREEN"\n Client connect Works Well \n"RESET);
    }
    else
    {
        printf(RED"\n Client connect NOT Works Well \n"RESET);
    }
    ClientDestroy(&client);

}

void ClientSendToRegTEST()
{
    ClientNet *client = NULL;
	ClientNet_Result status;
	int port = 2345;
	char address[] = "127.0.0.1";

    char messageToSend[100] = "1Benny you are amaizing";
    size_t length;

    length = strlen(messageToSend);
	client = ClientCreate(address, port);
    ConnectionWithTheServer(client);
    if(CLIENT_SUCCESSS ==SendTo(client,messageToSend,length))
    {
        printf(GREEN"\n Client SendTo Works Well \n"RESET);
    }
    else
    {
        printf(RED"\n Client SendTo NOT Works Well \n"RESET);
    }
    ClientDestroy(&client);
}

void ClientSendToLOGINTEST()
{
    ClientNet *client = NULL;
	ClientNet_Result status;
	int port = 2345;
	char address[] = "127.0.0.1";

    char messageToSend[100] = "3Benny you are amaizing";
    size_t length;

    length = strlen(messageToSend);
	client = ClientCreate(address, port);
    ConnectionWithTheServer(client);
    if(CLIENT_SUCCESSS ==SendTo(client,messageToSend,length))
    {
        printf(GREEN"\n Client SendTo Works Well \n"RESET);
    }
    else
    {
        printf(RED"\n Client SendTo NOT Works Well \n"RESET);
    }
    ClientDestroy(&client);
}

void ClientRecvTEST()
{
    ClientNet *client = NULL;
	ClientNet_Result status;
	int port = 2345;
	char address[] = "127.0.0.1";

    char messageToSend[100] = "1Benny you are amaizing";
    char buffer[100];

    size_t length;

    length = strlen(messageToSend);

	client = ClientCreate(address, port);

    ConnectionWithTheServer(client);
    SendTo(client,messageToSend,length);

    if(CLIENT_SUCCESSS == Recvfrom(client,buffer,sizeof(buffer)))
    {
    	printf("%s\n", (char*)buffer);
        printf(GREEN"\n Client Recvfrom Works Well \n"RESET);
    }
 
    ClientDestroy(&client);
}

int main() 
{
    /*ClientCreateTEST();
    ClientDestroyTEST();
    ClientConnectTEST();
    ClientSendTotTEST();
    ClientSendToLOGINTEST();
    ClientSendToRegTEST();*/
    ClientRecvTEST();
    return 0;
}
