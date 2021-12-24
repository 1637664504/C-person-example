#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "sys_thread.h"
#include "common/network/sys_network.h"
#include "monitor_interface_netlink.h"

#ifdef DEBUG
#define UNIT_TEST 1
#endif

#define WAN_IFCNAME "eth1"
#define MAX_WAIT_TIME 4

void* wan_judge_interface(void *arg)
{
    char ip[16];
#if UNIT_TEST
    struct thread_manage *thread = (struct thread_manage *)arg;
    char *ifc_name = WAN_IFCNAME;
#else
    struct monitor_thread *thread_info = (struct monitor_thread *)arg;
    struct thread_manage *thread = &thread_info->wan_manage;
    char *ifc_name = thread_info->ifcname;
#endif
    unsigned int wait_time_list[] = {4,4,4,MAX_WAIT_TIME};
    unsigned int wait_time = 4;
    int wait_count = 0;
    int ret;

    while(1)
    {
        if(thread->state != thread_running)
        {
            printf("WAN task suspend\n");
            thread_manage_suspend(thread, 0);
            wait_count = 0;
        }

        ret = 0;
        memset(ip,0,sizeof(ip));

        if(get_link_ip(ifc_name,ip,sizeof(ip)-1) == 0)
        {
            printf("WAN get ip=%s\n",ip);
            ret = 1;
        }
        else
        {
            printf("WAN not find ip\n");
        }

        if(ret)
        {
            wait_count = 0;
            thread_manage_stop(thread);
            send_cmd_to_main_thread(thread_info,CMD_WAN_FINISH);
        }
        else
        {
            if(wait_count > (sizeof(wait_time_list)/wait_time_list[0]-1))
            {
                printf("WAN Not get wan_ip. Set to LAN\n");
                thread_manage_stop(thread);
                send_cmd_to_main_thread(thread_info,CMD_LAN_FINISH);
            }
            else
            {
                wait_time =wait_time_list[wait_count];
            }

            printf("WAN wait_count=%d, wait_time=%u\n",wait_count,wait_time);
            thread_manage_wait_wakeup(thread, wait_time);
            wait_count ++;
        }
    }

    return NULL;
}

int wan_judge_thread_manage_create(struct monitor_thread *thread_info)
{
    pthread_t tid;
    int status = -1;

    if(!thread_info)
        return -1;

    thread_manage_init(&thread_info->wan_manage);
    status = pthread_create(&tid, NULL, wan_judge_interface, thread_info);
    if(status != 0)
    {
        perror("pthread_create error");
    }
    pthread_detach(tid);

    return 0;
}

#if UNIT_TEST
int main(void)
{
    pthread_t tid;
    void **retval;
    struct thread_manage wan_judge_thread;

    thread_manage_init(&wan_judge_thread);
    int status = pthread_create(&tid, NULL, wan_judge_interface, &wan_judge_thread);
    if(status != 0)
    {
        perror("pthread_create error");
    }
    pthread_detach(tid);
    //pthread_join(tid,&ret);

    char cmd[16];
    while(1)
    {
        printf("please inpud cmd: s-stop r-runing\n");
        scanf("%s",cmd);
        if(cmd[0] == 'r')
        {
            thread_manage_wakeup(&wan_judge_thread);
        }
        else if(cmd[0] == 's')
        {
            thread_manage_stop(&wan_judge_thread);
        }
        else if(cmd[0] == 'e')
        {
            exit(0);
        }
        else if(cmd[0] == 'l')
        {
            printf("task state=%d\n",wan_judge_thread.state);
        }
    }

    return 0;
}
#endif