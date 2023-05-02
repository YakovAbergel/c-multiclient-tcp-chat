#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void OpenChat(char* _ip, char* _port, char* _userName, char* _groupName, int* _receverPid, int* _senderPid)
{

	 char sender[300];
    char reciver[300];
    char GM[100];
    char UM[100];
    FILE *senderFile, *reciverFile;
    sprintf (GM, "%s_Group_Message_Screen", _groupName);
    sprintf (UM, "%s_Chat_KeyBoard_Screen", _groupName);
    sprintf(reciver, "gnome-terminal --geometry=80X14 --title %s  -- ./Reciver.out %s %s %s", GM, _ip, _port, _groupName);
    system (reciver);
    sprintf(sender, "gnome-terminal  --geometry=80X14 --title %s  -- ./Sender.out %s %s %s", UM, _ip, _port, _userName);
    system (sender);
    reciverFile = fopen ("reciver.txt", "r");
    fscanf (reciverFile, "%d", _receverPid);
    senderFile = fopen ("sender.txt", "r");
    fscanf (senderFile, "%d", _senderPid);














	/*static int location;
	char reciver[] = " -- ./Reciver.out";
	char sender[] = " -- ./Sender.out";
	char senderBuff[300];
    char reciverBuff[300];
    char GM[100];
    char UM[100];
    FILE *PIDfile = NULL;
   
    sprintf (GM, "%s_Group_Message_Screen", _groupName);
    sprintf (UM, "%s_Chat_KeyBoard_Screen", _groupName);
    sprintf(reciverBuff, "gnome-terminal --geometry=15X15+%d+0 --title=%s %s %s %s", location, GM, reciver,  _ip, _port);
    sprintf(senderBuff, "gnome-terminal  --geometry=15X5+%d+340 --title=%s %s %s %s %s",location, UM, sender,_ip, _port, _userName);
    if(system (reciverBuff) == -1)
    {
    	return;
    }
    if(system (senderBuff) == -1)
    {
    	return;
    }
    if((PIDfile = fopen ("reciver.txt", "r")) != NULL)
    {
    	while(!feof(PIDfile))
    	{
    	    fscanf (PIDfile, "%d", _receverPid);
    	}
    	fclose(PIDfile);
    }
    if((PIDfile = fopen ("sender.txt", "r")) != NULL)
    {
    	while(!feof(PIDfile))
    	{
    	    fscanf (PIDfile, "%d", _senderPid);
    	}
    	fclose(PIDfile);
    }*/
   
}

