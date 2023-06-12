#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXLINE 256

int main(int argc, char** argv)
{
    char sendline[MAXLINE];
    struct sockaddr_in    servaddr;
    int sockfd;
    unsigned short port = 9911;

    if( argc != 3){
        printf("usage: ./client ip port\n");
        exit(0);
    }
    port = (unsigned short)atoi(argv[2]);

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
        exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
        printf("inet_pton error for %s\n",argv[1]);
        exit(0);
    }

    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

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

        if(send(sockfd, sendline, strlen(sendline), 0) < 0)
        {
            printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
            exit(0);
        }
    }

    close(sockfd);
    return 0;
}