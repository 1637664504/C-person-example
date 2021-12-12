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

#define BUFLEN 2048

char monitor_list[][16]={
    "eth1"
};

int monitor_interface_check(const char *ifcname)
{
    int ret = -1;
    for(int i=0; i< sizeof(monitor_list)/sizeof(monitor_list[0]); i++)
    {
        if(strcmp(ifcname,monitor_list[i]) == 0)
        {
            ret = 0;
            break;
        }
    }

    return ret;
}

int handler_netlink_msg(const char *buf,int buf_len)
{
    struct nlmsghdr *nh;
    struct ifinfomsg *ifinfo;
    struct rtattr *attr;
    char ifcname[16]="";
    int nl_len = buf_len;
    int len;
    int ret = -1;
    
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
				ret = monitor_interface_check(ifcname);
                //1.显示msg down/up通知
				break;
			}
		}
        printf(" -----\n");
	}
}


int monitor_interface_netlink_init()
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

#if 0
int monitor_interface_netlink()
#else
int main (int argc, char *argv[])
#endif
{
	int fd;
	char buf[BUFLEN] = { 0 };
	fd = listen_interface_netlink_init();

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
            printf("select timeout\n");
            continue;
        }
        if(FD_ISSET(fd, &fds) && ((ret = read(fd, buf, BUFLEN)) > 0))
		{
			handler_netlink_msg(buf,ret);
		}
	}

	return 0;
}
