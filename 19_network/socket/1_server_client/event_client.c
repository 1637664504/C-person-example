#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
//#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static int event_socket_client_init(const char *path, struct sockaddr_un *addr)
{
    int sock;
    int server_len;

    if(!path || !addr)
        return -1;

    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock <= 0)
        return -2;

    addr->sun_family = AF_UNIX;
    strcpy(addr->sun_path, path);
    server_len = sizeof(struct sockaddr_un);
    if(connect(sock, (struct sockaddr *)addr, server_len) == -1)
    {
        printf("listen error: %d-%s",errno,strerror(errno));
        return -3;
    }

    return sock;
}

int send_event(const int sock,enum event_program program,const void *info,const unsigned int info_len)
{
    int ret;
    struct event_msg msg;
    int msg_len;

    msg.program = program;
    if(msg.program = malloc(info_len) == NULL)
        return -1;
    memcpy(msg.info,info,info_len);

    msg_len = (sizeof(msg)-sizeof(msg.info))+info_len;
    ret = write(sock,&msg,msg_len);

    return ret;
}

int register_event(struct event_client *client,enum event_program program)
{
    int ret = -1;
    struct sockaddr_un service_addr;
    int sock;
    struct info_monitor info; 

    sock = event_socket_client_init(EVENT_SOCKET_NAME,&service_addr);
    if(sock != 0)
        return sock;

    info.event_type = PROGRAM_REGISTER_EVENT;
    info.program = program;
    ret = send_event(sock,EVENT_PROGRAM_MONITOR,&info,sizeof(info));
    if(ret > 0)
    {
        client->event_fd = sock;
        client->program = program;
        ret = 0;
    }

    return ret;
}

int unregister_event(struct event_client *client)
{
    struct sockaddr_un service_addr;
    struct info_monitor info;

    info.event_type = PROGRAM_UNREGISTER_EVENT;
    info.program = client->program;
    send_event(client->event_fd,EVENT_PROGRAM_MONITOR,&info,sizeof(info));
    close(client->event_fd);

    return 0;
}

