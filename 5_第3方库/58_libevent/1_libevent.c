#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <assert.h>

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>

#define SERVER_PORT 5566
static void
accept_cb(evutil_socket_t fd, short events, void *arg)
{
	printf("liuj-- 111111111\n");
}
int create_socket()
{
    int server_sockfd,client_sockfd;
    struct sockaddr_in s_addr,c_addr;
    int len;
    int count=0;

    //server bind
    server_sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(server_sockfd < 0){
        perror("socket error");
        exit(1);
    }
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(SERVER_PORT);
    s_addr.sin_addr.s_addr = inet_addr("192.168.1.5");
    bind(server_sockfd,(struct sockaddr*)&s_addr,sizeof(s_addr));
    listen(server_sockfd,5);

	return server_sockfd;
}

int file_fd()
{
	return 0;
}

int main()
{
    int sockfd = create_socket();
    //int sockfd = file_fd();

    struct event_base * base = event_init();
    assert( base != NULL );

    struct event* ev_sock = event_new(base,sockfd,EV_READ|EV_PERSIST,accept_cb,(void*)base);
    assert( ev_sock != NULL );
    event_add(ev_sock,NULL);

    event_base_dispatch(base);
    event_free(ev_sock);
    event_base_free(base);
}

