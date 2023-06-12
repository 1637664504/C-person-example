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

#define MAXLINE 1024
struct topic_manage manage;

int fd_set_nonblock(int fd)
{
    int ret;
    int flags = fcntl(fd, F_GETFL, 0);
    ret = fcntl(fd, F_SETFL, flags|O_NONBLOCK);

    return ret;
}

void broadcast_publish_msg(struct topic *item,struct pub_msg *pub_msg)
{
    int i=0;
    for(i=0; i<TOPIC_MAX_SUB_CLIENT; i++){
        if(item->sub_fd[i])
            write(item->sub_fd[i],pub_msg->info,pub_msg->len);
    }
}

void handler_connect(int *sock_fd)
{
    char buf[2048]="";
    unsigned int len = 0;
    struct topic *item;
    unsigned char code = 0;
    int sock = *sock_fd;

    len = recv(sock, &buf, sizeof(buf), 0);
    if(len < 0)
    {
        printf("recv failed\n");
        return ;
    }
    else if(len == 0)
    {
        printf("close this client sock");
        topic_del_fd(&manage,sock);
        close(*sock_fd);
        *sock_fd = 0;
        return ;
    }
    
    code = (unsigned char)buf[0];
    if(code == TOPIC_PUB)
    {
        struct pub_msg *msg = (struct pub_msg *)buf;
        printf("pub %s - msg=%s\n",msg->topic_name,(char *)&msg->info);
        if((item = topic_search(&manage,msg->topic_name)) != NULL)
        {
            broadcast_publish_msg(item,msg);
        }
        close(*sock_fd);
        *sock_fd = 0;
    }
    else if(code == TOPIC_SUB)
    {
        struct sub_msg *msg = (struct sub_msg *)buf;
        printf("sub %s\n",msg->topic_name);
        if((item = topic_search(&manage,msg->topic_name)) != NULL)
        {
            //has exist
            topic_add_fd(item,sock);
        }
        else
        {
            if((item = topic_add(&manage,msg->topic_name)) != NULL)
                topic_add_fd(item,sock);
        }
    }

}

int main(int argc, char** argv)
{
    int listenfd;
    int connfd = 0;
    struct sockaddr_in servaddr;
    fd_set rd_set;
    struct timeval tm;
    int max_fd = 0;

    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    //servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0){
        printf("inet_pton error for \n");
        exit(0);
    }

    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    if( listen(listenfd, 10) == -1){
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    
    topic_manage_init(&manage);

    printf("======waiting for client's request======\n");
    while(1){
        int ret = -1;

        FD_ZERO(&rd_set);
        FD_SET(listenfd, &rd_set);

        max_fd = listenfd+1;
        if(connfd)
        {
            FD_SET(connfd, &rd_set);
            if(max_fd <= connfd)
                max_fd = connfd+1;
        }

        memset(&tm,0,sizeof(tm));
        tm.tv_sec = 32;

        ret = select(max_fd,&rd_set,NULL,NULL,NULL);
        if(ret < 0)
        {
            perror("select fail\n");
            exit(-1);
        }
        else if(ret == 0)
        {
            printf("select timeout\n");
            continue;
        }

        if(FD_ISSET(listenfd,&rd_set))
        {
            if((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1){
                printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
                continue;
            }
            fd_set_nonblock(connfd);
            printf("new connect\n");
        }

        else if(FD_ISSET(connfd,&rd_set))
        {
            handler_connect(&connfd);
        #if 0
            len = recv(connfd, buff, MAXLINE, 0);
            //len = read(connfd,buff,MAXLINE);
            if(len > 0)
            {
                printf("recv msg from client: %s\n", buff);
                handler_connect()
            }
            else if(len == 0)
            {
                printf("recv len=%d, error=%d::%s\n", len,errno,strerror(errno));
                close(connfd);
                connfd = 0;
                sleep(1);
            }
            else if(len < 0)
            {
                printf("recv failed len=%d, error=%d::%s\n", len,errno,strerror(errno));
                sleep(1);
            }
        #endif
        }

    }

    close(listenfd);
}