#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

//#include "lib/common.h"
//#include "lib/client_info.h"

char unix_socket_name[32] = "/tmp/test_unix_sock";

int unix_socket_client_init(const char *path, struct sockaddr_un *addr)
{
    int sock;
    int server_len;

    if(!path || !addr || !client_num)
        return -1;

    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock <= 0)
        return -1;

    unlink(path);
    addr->sun_family = AF_UNIX;
    strcpy(addr->sun_path, path);
    server_len = sizeof(struct sockaddr_un);
    connect(sock, (struct sockaddr *)addr, server_len);

    return sock;
}

int main(int argc, char *argv[])
{
    char sendline[64];
    int sockfd = 0;
    int client_len;
    struct sockaddr_un server_address;

    sockfd = unix_socket_client_init(unix_socket_name,&server_address);
    fd_set_nonblock(sockfd);
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
    unlink(unix_socket_name);

    return 0;
}

