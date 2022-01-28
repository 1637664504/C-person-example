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
#include "event.h"

#include "event.h"

void handler_monitor_event(struct info_monitor *info)
{
    if(info->event_type == PROGRAM_REGISTER_EVENT)
    {
        
    }
    else if(info->event_type == PROGRAM_UNREGISTER_EVENT)
    {

    }
}

void handler_wan_lan_event(struct info_wan_lan *info)
{
    printf("%s,%d\n",info->ifcname,info->adapt);
}

void handler_multi_wan_event(struct info_mutil_wan *info)
{
    printf("pri: %s,%u ---- bak:%s %u\n",info->ifcname,info->score,info->back_ifcname,info->back_score);
}

void handler_event(struct event_msg *msg)
{
    switch(msg->program)
    {
        case EVENT_PROGRAM_MONITOR:
            handler_monitor_event((struct info_monitor*)msg->info);
            break;
        case EVENT_PROGRAM_WAN_LAN:
            handler_wan_lan_event((struct info_wan_lan *)msg->info);
            break;
        case EVENT_PROGRAM_MULTI_WAN:
            handler_multi_wan_event((struct info_mutil_wan*)msg->info);
            break;
        default:
            printf("not support program\n");
            break;
    }
}
