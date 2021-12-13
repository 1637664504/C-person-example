#include <sys/types.h>
#include <sys/socket.h>
#include <asm/types.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <string.h>
#include <pthread.h>
#include "monitor_interface_netlink.h"


#define BUFLEN 2048

static char monitor_link[16] = "eth2";
struct monitor_thread g_monitor_thread;

int netlink_sock_init()
{
    int fd;
    int len = BUFLEN;
    struct sockaddr_nl addr;

    fd = socket (AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    setsockopt (fd, SOL_SOCKET, SO_RCVBUF, &len, sizeof (len));
    memset (&addr, 0, sizeof (addr));
    addr.nl_family = AF_NETLINK;
    addr.nl_groups = RTNLGRP_LINK;
    if (bind (fd, (struct sockaddr *) &addr, sizeof (addr)))
    {
        printf ("bind sock fail");
        return 0;
    }

    return fd;
}

int monitor_thread_init(struct monitor_thread *thread,const char *ifc_name)
{
    int ret = 0;

    strncpy(thread->ifcname,ifc_name,sizeof(thread->ifcname)-1);
    if((ret = pipe(thread->pipefd)) != 0)
    {
        ret = -1;
    }
    //lan_listen_dhcp_thread_manage_create(thread);
    wan_judge_thread_manage_create(thread);

    return ret;
}

void handler_interface_status_change(unsigned ifc_flags)
{
    int up = (ifc_flags & IFF_LOWER_UP) ? 1 : 0;

    printf("handler link status change \n");
    struct thread_manage *lan_thread = &g_monitor_thread.lan_manage;
    struct thread_manage *wan_thread = &g_monitor_thread.wan_manage;
    if(up)
    {
        printf("link up 111\n");
        //thread_manage_wakeup(lan_thread);
        thread_manage_wakeup(wan_thread);
        printf("link up 222\n");
    }
    else
    {
        printf("link down 111\n");
        //thread_manage_stop(lan_thread);
        thread_manage_stop(wan_thread);
        printf("link down 222\n");
    }

    return ;
}

int handler_netlink_msg(const char *buf,int buf_len)
{
    struct nlmsghdr *nh;
    struct ifinfomsg *ifinfo;
    struct rtattr *attr;
    char ifcname[16]="";
    int nl_len = buf_len;
    int len;

    for (nh = (struct nlmsghdr *) buf; NLMSG_OK (nh, nl_len); nh = NLMSG_NEXT (nh, nl_len))
    {
        if (nh->nlmsg_type == NLMSG_DONE)
            break;
        else if (nh->nlmsg_type == NLMSG_ERROR)
            return -1;
        else if (nh->nlmsg_type != RTM_NEWLINK)
            continue;
        ifinfo = NLMSG_DATA (nh);
        printf ("%u: %s", ifinfo->ifi_index, (ifinfo->ifi_flags & IFF_LOWER_UP) ? "up" : "down");
        attr = (struct rtattr *) (((char *) nh) + NLMSG_SPACE (sizeof (*ifinfo)));
        len = nh->nlmsg_len - NLMSG_SPACE (sizeof (*ifinfo));
        for (; RTA_OK (attr, len); attr = RTA_NEXT (attr, len))
        {
            if (attr->rta_type == IFLA_IFNAME)
            {
                //printf (" %s", (char *) RTA_DATA (attr));
                strncpy(ifcname,(char *)RTA_DATA (attr),sizeof(ifcname)-1);
                printf (" %s", ifcname);
                if(strcmp(ifcname, g_monitor_thread.ifcname) == 0)
                    handler_interface_status_change(ifinfo->ifi_flags);

                break;
            }
        }
        printf(" -----\n");
    }

    return 0;
}

#if 0
int monitor_interface_netlink()
#else
int main (int argc, char *argv[])
#endif
{
    int fd;
    char buf[BUFLEN] = { 0 };

    fd = netlink_sock_init();
    monitor_thread_init(&g_monitor_thread,monitor_link);

    while (1)
    {
        struct timeval tv;
        fd_set fds;
        int ret;

        tv.tv_sec=5;
        tv.tv_usec=0;
        FD_ZERO(&fds);
        FD_SET(fd,&fds);

        ret = select(fd+1, &fds, NULL, NULL, &tv);
        if(ret < 0)
        {
            perror("select fail");
            return ret;
        }
        else if(ret == 0)
        {
            printf("netlink select timeout\n");
            continue;
        }

        if(FD_ISSET(fd, &fds) && ((ret = read(fd, buf, BUFLEN)) > 0))
        {
            handler_netlink_msg(buf,ret);
        }
    }

    return 0;
}
