#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

#include "lib/array/sortArray.h"
#include "lib/common_sys.h"
#define MAXLINE 1024

int get_trigger_fd(int fd[],int count,fd_set *set)
{
    int trigger_fd = 0;
    int i;
    for(i=0;i<count;i++)
    {
        if(FD_ISSET(fd[i],set))
        {
            trigger_fd = fd[i];
        }
    }

    return trigger_fd;
}

int client_fds_set(struct sortArray *clnt,fd_set *set)
{
    int i = 0;
    clnt->show(clnt);
    for( ;i<clnt->count;i++){
        FD_SET(clnt->array[i],set);
    }

    return i;
}

int main(int argc, char** argv)
{
    int listenfd;
    int connfd = 0;
    struct sockaddr_in     servaddr;
    char    buff[4096];
    int     len;
    fd_set rd_set;
    struct timeval tm;
    int max_fd = 0;
    unsigned short port = 9911;
    char ip[16] = "127.0.0.1";

    if( argc == 3){
        printf("usage: ./client ip port\n");
        port = (unsigned short)atoi(argv[2]);
        strncpy(ip,argv[1],sizeof(ip)-1);
        //exit(0);
    }

    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    //servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(inet_pton(AF_INET, ip, &servaddr.sin_addr) <= 0){
        printf("inet_pton error for %s\n",argv[1]);
        exit(0);
    }

    if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }
    if( listen(listenfd, 10) == -1){
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }
    max_fd = listenfd;

    struct sortArray *client_fds;
    sortArray_init(&client_fds,16);

    printf("======waiting for client's request======\n");
    while(1){
        int ret = -1;

        FD_ZERO(&rd_set);
        FD_SET(listenfd, &rd_set);
        if(client_fds_set(client_fds,&rd_set))
            max_fd = client_fds->getMax(client_fds);

        printf("max_fd=%d, client=%d\n",max_fd,client_fds->array[client_fds->count]);

        memset(&tm,0,sizeof(tm));
        tm.tv_sec = 4;

        ret = select(max_fd+1,&rd_set,NULL,NULL,NULL);
        if(ret < 0)
        {
            printf("select fail error=%d::%s\n", errno,strerror(errno));
            if(errno == EBADF)
            {
                connfd = get_trigger_fd(client_fds->array,client_fds->count,&rd_set);
                client_fds->del(client_fds,connfd);
                continue;
            }
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
            //fd_set_nonblock(connfd);
            client_fds->add(client_fds,connfd);
            client_fds->show(client_fds);
            continue;
        }

        client_fds->show(client_fds);
        connfd = get_trigger_fd(client_fds->array,client_fds->count,&rd_set);
        if(connfd)
        {
            len = read(connfd,buff,MAXLINE);
            if(len > 0)
                printf("recv msg from client: %s\n", buff);
            else if(len == 0)
            {
                printf("recv len=%d, error=%d::%s\n", len,errno,strerror(errno));
                close(connfd);
                client_fds->del(client_fds,connfd);
            }
            else if(len < 0)
            {
                printf("recv failed len=%d, error=%d::%s\n", len,errno,strerror(errno));
            }
        }
    }

    close(listenfd);
    sortArray_release(client_fds);
}