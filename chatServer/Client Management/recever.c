/* reciver*/
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>


#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ChatProtocol.h"


int main(int argc, char *argv[])
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    int read_bytes, sent_bytes;
    struct sockaddr_in sin;
    struct ip_mreq mreq;
    struct in_addr localInterface;
    socklen_t sokket = sizeof (sin);
    char buffer[4096];
    char userName[MAX_NAME_LENGTH];
    char msg[MAX_MASSAGE_LENGTH];
    char* ip = argv[1];
    int port = atoi(argv[2]);
    char stop[] = "exit";
    int tag, status;
    int yes = 1;
    int pid;
    FILE* file;
    pid = getpid();
    if (argc != 4)
    {
        printf ("wrong input\n");
        return 0;
    }
    if ((file = fopen ("reciver.txt", "w")) == NULL)
    {
        printf ("Error in opening file\n");
        return 0;
    }
    else 
    {
        fprintf (file,"%d",pid);
        fclose (file);
    }
    memset(&sin, 0, sizeof(sin));
    if (sock < 0)
    {
        perror ("socket failed");
        return 0;
    }
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip);
    sin.sin_port = htons(port);

    if (setsockopt (sock, SOL_SOCKET, SO_REUSEADDR,(char *)&yes, sizeof(yes)) < 0)
    {
        perror("Reusing ADDR faieled");
        close(socket);
        return 0;
    }
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0)
    {
        perror("bind failed");
        return 0;
    }



    /*localInterface.s_addr = inet_addr(ip);
    if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, (char*)&localInterface, sizeof(localInterface)) < 0) 
    {
        perror("setting local interface");
        return (0);
    }*/
  

    
    mreq.imr_multiaddr.s_addr = inet_addr(ip);
    mreq.imr_interface.s_addr = INADDR_ANY/*htons (INADDR_ANY)*/;

    if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*) &mreq, sizeof(mreq)) < 0)
    {
        perror("setsockopt");
        return 0;
    }
    printf ("welcome to %s Group\n", argv[3]);
    while (strcmp ("exit", msg) != 0)
    {
        read_bytes = recvfrom(sock, buffer, sizeof(buffer), 0,
        (struct sockaddr *) &sin, &sokket);

        if (read_bytes < 0)
        {
            perror("recvfrom failed");
            return 0;
        }

        ProtocolRequestReciveMsg (buffer, userName, msg);
        tag = GetTag (buffer);

        printf ("%s: %s\n", userName, msg);
        ProtocolReplyReciveMsg (buffer, &status);
        /*need to be canceled*/
        /*sent_bytes = sendto(sock, (void*)buffer, strlen (buffer), 0,
                    (struct sockaddr*)&sin, sizeof(sin));

        if (sent_bytes < 0)
        {
            perror("sendto failed");
            return 0;
        }*/
    }
    close (sock);
    return 0;
}
