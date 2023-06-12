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

#define MAXLINE 256
const char unix_socket_name[32] = "test_unix_sock";

int unix_socket_client_init(const char *path, struct sockaddr_un *addr)
{
    int sock;
    int server_len;

    if(!path || !addr)
        return -1;

    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock <= 0)
        return -1;

    addr->sun_family = AF_UNIX;
    strcpy(addr->sun_path, path);
    server_len = sizeof(struct sockaddr_un);
    if(connect(sock, (struct sockaddr *)addr, server_len) == -1)
    {
        printf("listen error: %d-%s",errno,strerror(errno));
        exit(-1);
    }

    return sock;
}

int main(int argc, char** argv)
{
    char sendline[MAXLINE];
    struct sockaddr_un servaddr;
    int sockfd;

    sockfd = unix_socket_client_init(unix_socket_name,&servaddr);

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