#ifndef monitor_interface_netlink_h
#define monitor_interface_netlink_h


#define LAN_MAX_NUM 4
struct monitor_thread_info{
	char ifcname[16];
	int pipefd[2];
	struct thread_manage lan_manage;
	struct thread_manage wan_manage;
};


#endif
