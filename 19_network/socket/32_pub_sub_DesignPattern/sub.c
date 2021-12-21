#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include "topic.h"
#include "pub_sub.h"


int subscribe_topics(const char *topic_name,int sock)
{
    struct sub_msg msg;
    msg.code = TOPIC_SUB;
    strncpy(msg.topic_name,topic_name,sizeof(msg.topic_name));

    send(sock, &msg, sizeof(msg), 0);
    return 0;
}

int tpoic_sock_init(const char*ip)
{
    int sockfd;
    struct sockaddr_in    servaddr;
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
        exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    if(inet_pton(AF_INET, ip, &servaddr.sin_addr) <= 0){
        printf("inet_pton error for %s\n",ip);
        exit(0);
    }

    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    return sockfd;
}

int main(void)
{
    int sock;
    char topic[32] = "test";
    sock = tpoic_sock_init("127.0.0.1");
    subscribe_topics(topic,sock);
    while(1)
    {
        unsigned int len = 0;
        char msg[2048];
        len = read(sock,msg,sizeof(msg)-1);
        printf("msg=%s\n",msg);

        if(len == 0)
            break;
    }

    return 0;
}
