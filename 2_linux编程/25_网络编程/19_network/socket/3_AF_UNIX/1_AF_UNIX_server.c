#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "lib/common.h"
#include "lib/client_info.h"

char unix_socket_name[32] = "/tmp/test_unix_sock";

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
    server->sun_family = AF_UNIX;
    strcpy(server->sun_path, path);
    server_len = sizeof(struct sockaddr_un);

    bind(sock, (struct sockaddr *)server, server_len);
    listen(sock, client_num);

    return sock;
}

int main(int argc, char *argv[])
{
    int server_sockfd = 0;
    int client_sockfd = 0;
    int client_len;
    struct sockaddr_un server_address;

    fd_set rfds;
    struct timeval tm;
    int ret;
    int max_fd;
    struct client_manage *client_mg = NULL;

    client_manage_init(&client_mg,5);
    server_sockfd = unix_socket_server_init(unix_socket_name,&server_address,5);
    fd_set_nonblock(server_sockfd);
    while(1)
    {
        FD_ZERO(&rfds);
        FD_SET(server_sockfd, &rfds);
        max_fd = client_mg->max_fd;
        memset(&tm,0,sizeof(tm));
        tm.tv_sec = 16;

        ret = select(max_fd+1, &rfds, NULL, NULL, &tm);
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

        if(FD_ISSET(server_sockfd,&rfds))
        {
            client_sockfd = accept(server_sockfd, (struct sockaddr *)&server_address,(socklen_t *)&client_len);
            if (client_sockfd == -1) {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            client_manage_add(client_mg,client_sockfd);
            continue;
        }

        char buf[64] = "";
        int set_fd = 0;
        int len;
        set_fd = client_manage_get_select_fd(client_mg,&rfds);
        if(set_fd)
        {
            len = read(set_fd,buf,sizeof(buf)-1);
            if(len > 0)
            {
                debugLog("fd=%d: recv_buf=%s",set_fd,buf);
            }
            else if(len == 0)
            {
                if(errno == 0)
                {
                    client_manage_del(client_mg,set_fd);
                    close(set_fd);
                    debugLog("client disconn fd=%d",set_fd);
                }
            }
            else if(len < 0)
            {
                if (errno == EINTR)
                {
                    continue;
                }
                debugLog("read error fd=%d",set_fd);
                exit(-1);
            }
        }
    }

    client_manage_close_all(client_mg);
    close(server_sockfd);
    unlink(unix_socket_name);

    return 0;
}
