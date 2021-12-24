#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "common.h"

int send_event(enum jrd_events_type type,void *event,unsigned int info_len)
{
    int sock;
    struct sockaddr_in servaddr;
    struct jrd_event_msg *msg;
    unsigned int len;

    if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("create socket failed\n");
        return -1;
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(JRD_EVENT_PORT);
    servaddr.sin_addr.s_addr = inet_addr(JRD_EVENT_IP);

    len = (sizeof(*msg)-sizeof(msg->info))+info_len;
    if((msg = malloc(len)) != NULL)
    {
        msg->event = type;
        memcpy(&msg->info,event,info_len);
        sendto(sock, msg, len, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
    }

    close(sock);
    if(msg)
        free(msg);

    return 0;
}

int main(void)
{
#if debug
    int sock;
    struct sockaddr_in servaddr;

    if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("create socket failed\n");
        exit(-1);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(JRD_EVENT_PORT);
    servaddr.sin_addr.s_addr = inet_addr(JRD_EVENT_IP);

    struct wan_change_event event;
    strcpy(event.interface,"eth1");
    event.status = 1;

    struct jrd_event_msg *msg;
    msg = malloc(1024);
    msg->event = WAN_CHANGE_EVENT;
    memcpy(&msg->info,&event,sizeof(event));

    sendto(sock, msg, len, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
    close(sock);
#else
    struct wan_change_event event;
    strcpy(event.interface,"eth4");
    event.status = 1;
    send_event(WAN_CHANGE_EVENT,(void *)&event,sizeof(event));
#endif
    
    return 0;
}