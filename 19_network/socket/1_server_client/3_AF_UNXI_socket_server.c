#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
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

const char unix_socket_name[32] = "test_unix_sock";

int unix_socket_server_init(const char *path, struct sockaddr_un *server, const unsigned int client_num)
{
    int sock;
    int server_len;

    if(!path || !server || !client_num)
        return -1;

    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock <= 0)
        return -1;

    unlink(path);
    memset(server,0,sizeof(*server));
    server->sun_family = AF_UNIX;
    strcpy(server->sun_path, path);
    server_len = sizeof(struct sockaddr_un);

    if(bind(sock, (struct sockaddr *)server, server_len) == -1)
    {
        printf("bind error: %d-%s",errno,strerror(errno));
        exit(-1);
    }
        
    if(listen(sock, client_num) == -1)
    {
        printf("listen error: %d-%s",errno,strerror(errno));
        exit(-1);
    }

    return sock;
}

int main(int argc, char** argv)
{
    char buff[1024];
    struct sockaddr_un servaddr;
    int listenfd;
    int connfd = 0;
    int len;

    int max_fd = 0;
    fd_set rd_set;
    struct timeval tm;

    listenfd = unix_socket_server_init(unix_socket_name,&servaddr,5);
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
        tm.tv_sec = 16;

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