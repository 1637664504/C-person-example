#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

#include "common.h"

void handler_wan_change(struct wan_change_event *event)
{
    printf("%s %d\n",event->interface,event->status);
}

void listen_event_main(int sock)
{
    char recvbuf[1024] = {0};
    struct sockaddr_in peeraddr;
    socklen_t peerlen;
    struct timeval tm;
    fd_set rd_set;
    int ret;
    int n;
    struct jrd_event_msg *msg;

    while (1)
    {
        FD_ZERO(&rd_set);
        FD_SET(sock, &rd_set);
        memset(&tm,0,sizeof(tm));
        tm.tv_sec = 16;

        ret = select(sock+1,&rd_set,NULL,NULL,&tm);
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

        peerlen = sizeof(peeraddr);
        memset(recvbuf, 0, sizeof(recvbuf));
        n = recvfrom(sock, recvbuf, sizeof(recvbuf), 0,
                     (struct sockaddr *)&peeraddr, &peerlen);
        if (n <= 0)
        {
            if (errno == EINTR)
                continue;
            exit(-1);
        }
        msg = (struct jrd_event_msg *)recvbuf;
        switch(msg->event)
        {
            case WAN_CHANGE_EVENT:
                handler_wan_change((struct wan_change_event *)&msg->info);
                break;
            default:
                break;
        }
    }
    close(sock);
}
 
int main(void)
{
    int sock;
    if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("create socket failed\n");
        exit(-1);
    }
    
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(JRD_EVENT_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("bind error\n");
        exit(-1);
    }
    
    listen_event_main(sock);
    
    return 0;
}