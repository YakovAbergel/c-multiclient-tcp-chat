/* sender*/
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include "ChatProtocol.h"
#define MAX_BUFFER_SIZE 256


int main (int argc, char *argv[])
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    int read_bytes, sent_bytes;
    struct sockaddr_in sin;
    socklen_t sokket = sizeof (sin);
    char message[MAX_MASSAGE_LENGTH];
    char userName[MAX_NAME_LENGTH];
    char buffer [MAX_BUFFER_SIZE];
    char* ip = argv[1];
    int tag, length, inputLength = 0, status, i;
    char stop[] = "exit";
    int pid;
    FILE* file;
    pid = getpid();
    if (argc != 4)
    {
        printf ("wrong input\n");
        return 0;
    }
    if ((file = fopen ("sender.txt", "w")) == NULL)
    {
        printf ("Error in opening file\n");
        return 0;
    }
    else 
    {
        fprintf (file,"%d",pid);
        fclose (file);
    }
    strcpy (userName, argv[3]);

    if (sock < 0)
    {
        perror ("socket failed");
        return 0;
    }
    
    printf ("Welcome %s!\nHere you can only type!\n", argv[3]);
    while (strcmp (message, stop) != 0)
    {
        fgets (message,MAX_MASSAGE_LENGTH,stdin);
        /*for ( i = 1; i < argc; i++)
        {
            strcpy ((message+inputLength), argv[i]);
            inputLength+= strlen (argv[i]);
            *(message+inputLength) = ' ';
            inputLength++;
        }*/

        ProtocolRequestSendMsg (buffer, userName, message);
        memset(&sin, 0, sizeof(sin));
        sin.sin_family = AF_INET;
    	sin.sin_addr.s_addr = inet_addr(ip);
   		 sin.sin_port = htons (atoi (argv[2]));
        sent_bytes = sendto(sock, (void*)buffer, strlen (buffer), 0, (struct sockaddr *) &sin, sizeof(sin));

        if (sent_bytes < 0)
        {
            perror("sendto failed");
            return 0;
        }
            
        /*read_bytes = recvfrom(sock, buffer, sizeof(buffer), 0,
        (struct sockaddr *) &sin, &sokket);
        buffer[read_bytes] ='\0';
        if (read_bytes < 0)
        {
            perror("recvfrom failed");
            return 0;
        }
        tag = GetTag (buffer);
        length = ProtocolReplySendMsg (buffer, &status);
        printf ("%d %d\n", tag, length);*/
   }
    close (sock);
    return 0;
}
