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


int publish_topics(const char *topic_name,const void *info,unsigned int info_len,int sock)
{
    struct pub_msg *msg;
    unsigned int len;

    len = sizeof(*msg)-sizeof(msg->info)+info_len;
    msg = malloc(len);
    msg->code = TOPIC_PUB;
    strncpy(msg->topic_name,topic_name,sizeof(msg->topic_name)-1);
    memcpy(&msg->info,info,info_len);

    send(sock, msg, len, 0);
    free(msg);

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

    //while(1)
    {
        char test[32]="hellow topic test";
        publish_topics(topic,test,strlen(test)+1,sock);
    }
    close(sock);

    return 0;
}

