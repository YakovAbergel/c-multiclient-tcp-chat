#include "clientManagment.h"
#include <stdio.h>

int main()
{
	ClientMan* client;
	
	client = ClientManageCreate("yakov");
	Client_Run(client); 
	return 0;
}

