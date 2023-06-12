#ifndef _monitor_interface_netlink_h
#define _monitor_interface_netlink_h

#include "sys_thread.h"


#define CMD_STOP    0
#define CMD_START   1
#define CMD_LAN_FINISH   2
#define CMD_WAN_FINISH   3

struct cmd_msg{
    pid_t tid;
    int cmd;
};

struct monitor_thread{
	char ifcname[16];
	int cmd_fd[2];
	struct thread_manage lan_manage;
	struct thread_manage wan_manage;
};

extern int lan_listen_dhcp_thread_manage_create(struct monitor_thread *thread_info);
extern int wan_judge_thread_manage_create(struct monitor_thread *thread_info);
extern void send_cmd_to_main_thread(struct monitor_thread *thread,int cmd);

#endif
