#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "event.h"
#include "event_client.h"

#define MAXLINE 256


int main(int argc, char** argv)
{
    char sendline[MAXLINE];
    struct sockaddr_un servaddr;
    int sockfd;

    sockfd = register_event();

    printf("server recv msg\n");
    while(1)
    {
        memset(sendline,'\0',sizeof(sendline));
        fgets(sendline, MAXLINE, stdin);
        if(sendline[0] == 'e')
        {
            close(sockfd);
            sockfd = 0;
            break;
        }

        send_event();
    }

    close(sockfd);
    return 0;
}