#ifndef _monitor_interface_netlink_h
#define _monitor_interface_netlink_h

#include "sys_thread.h"

struct monitor_thread{
	char ifcname[16];
	int pipefd[2];
	struct thread_manage lan_manage;
	struct thread_manage wan_manage;
};

extern int lan_listen_dhcp_thread_manage_create(struct monitor_thread *thread_info);
extern int wan_judge_thread_manage_create(struct monitor_thread *thread_info);

#endif
