#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXLINE 1024

int fd_set_nonblock(int fd)
{
    int ret;
    int flags = fcntl(fd, F_GETFL, 0);
    ret = fcntl(fd, F_SETFL, flags|O_NONBLOCK);

    return ret;
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

    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(6666);

    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    if( listen(listenfd, 10) == -1){
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    printf("======waiting for client's request======\n");
    while(1){
        int ret = -1;

        FD_ZERO(&rd_set);
        FD_SET(listenfd, &rd_set);
        if(connfd)
        {
            FD_SET(connfd, &rd_set);
            if(max_fd <= connfd)
                max_fd = connfd+1;
        }
        if(max_fd <= listenfd)
            max_fd = listenfd+1;

        memset(&tm,0,sizeof(tm));
        tm.tv_sec = 4;

        ret = select(max_fd,&rd_set,NULL,NULL,&tm);
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
        }
        else if(FD_ISSET(connfd,&rd_set))
        {
            len = recv(connfd, buff, MAXLINE, 0);
            //len = read(connfd,buff,MAXLINE);
            if(len > 0)
                printf("recv msg from client: %s\n", buff);
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
        }

    }

    close(listenfd);
}