#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <asm/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <linux/route.h>
#define BUFLEN 2048
 
#define t_assert(x) { \
	if(!(x))  {err = -__LINE__;goto error;} \
}

void parse_rtattr(struct rtattr **tb, int max, struct rtattr *attr, int len)
{
	for (; RTA_OK(attr, len); attr = RTA_NEXT(attr, len)) {
		if (attr->rta_type <= max) {
			tb[attr->rta_type] = attr;
		}
	}
}
 

void print_ifinfomsg(struct nlmsghdr *nh)
{
	int len;
	struct rtattr *tb[IFLA_MAX + 1];
	struct ifinfomsg *ifinfo;
	bzero(tb, sizeof(tb));
	ifinfo = NLMSG_DATA(nh);
	len = nh->nlmsg_len - NLMSG_SPACE(sizeof(*ifinfo));
	parse_rtattr(tb, IFLA_MAX, IFLA_RTA (ifinfo), len);
	printf("111 link down/up %s: %s ", (nh->nlmsg_type==RTM_NEWLINK)?"NEWLINK":"DELLINK", (ifinfo->ifi_flags & IFF_UP) ? "up" : "down");
	if(tb[IFLA_IFNAME]) {
		printf("%s", RTA_DATA(tb[IFLA_IFNAME]));
	}
	printf("\n");
}

int jrd_netlink_monito(int argc, char *argv[])
{
	int socket_fd;
	int err = 0;
	fd_set rd_set;
	struct timeval timeout;
	int select_r;
	int read_r;
	struct sockaddr_nl sa;
	struct nlmsghdr *nh;
 
 
	int len = BUFLEN;
	char buff[2048];
	//signal(SIGINT, intHandler);
 
	/*打开NetLink Socket*/
	socket_fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	t_assert(socket_fd > 0);
	t_assert(!setsockopt(socket_fd, SOL_SOCKET, SO_RCVBUF, &len, sizeof(len)));
 
	/*设定接收类型并绑定Socket*/
	bzero(&sa, sizeof(sa));
	sa.nl_family = AF_NETLINK;
	//sa.nl_groups = RTMGRP_LINK | RTMGRP_IPV4_IFADDR | RTMGRP_IPV4_ROUTE | RTMGRP_IPV6_IFADDR | RTMGRP_IPV6_ROUTE;
	sa.nl_groups = RTMGRP_LINK;
	t_assert(!bind(socket_fd, (struct sockaddr *) &sa, sizeof(sa)));
 
	while (1) {
		FD_ZERO(&rd_set);
		FD_SET(socket_fd, &rd_set);
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		select_r = select(socket_fd + 1, &rd_set, NULL, NULL, &timeout);
		if (select_r < 0) {
			perror("select");
		}
		else if(select_r == 0){
			printf("444 timeout --\n");
			continue;
		}
		else if (select_r > 0) {
			if (FD_ISSET(socket_fd, &rd_set)) {
				read_r = read(socket_fd, buff, sizeof(buff));
				for (nh = (struct nlmsghdr *) buff; NLMSG_OK(nh, read_r); nh = NLMSG_NEXT(nh, read_r)) {
					switch (nh->nlmsg_type) {
					case RTM_NEWLINK:
					case RTM_DELLINK:
						print_ifinfomsg(nh);
						break;
					default:
						/*收到些奇怪的信息*/
						printf("nh->nlmsg_type = %d\n", nh->nlmsg_type);
						break;
					}
				}
			}
		}
	}
 
	close(socket_fd);
 
error:
	if (err < 0) {
		printf("Error at line %d\nErrno=%d\n", -err, errno);
	}
	return err;
}