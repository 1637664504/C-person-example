#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "sys_thread.h"
#include "common/network/sys_network.h"

#define WAN_IFCNAME "eth1"
#define MAX_WAIT_TIME 8
void* wan_judge_interface(void *arg)
{
    char ip[16];
    struct thread_manage *thread = (struct thread_manage *)arg;
    unsigned int wait_time_list[] = {4,4,8,MAX_WAIT_TIME};
    unsigned int wait_time;
    int wait_count = 0;
    int ret;
    char *ifcname = WAN_IFCNAME;

    while(1)
    {
        if(thread->state != thread_running)
        {
            printf("task suspend\n");
            thread_manage_suspend(thread, 0);

            //restart thread init
            wait_count = 0;
        }
        //re-judge init
        ret = 0;
        memset(ip,0,sizeof(ip));

        if(get_link_ip(ifcname,ip,sizeof(ip)-1) == 0)
        {
            //1.set mem
            //2.ubus notify
            //3.puse or stop
            printf("get ip=%s\n",ip);
            ret = 1;
        }
        else{
            //sleep
            printf("not find ip\n");
        }

        if(ret)
        {
            thread_manage_stop(thread);
            wait_count = 0;
        }
        else
        {
            if(wait_count > (sizeof(wait_time_list)/wait_time_list[0]-1))
                wait_time = MAX_WAIT_TIME;
            else
                wait_time =wait_time_list[wait_count];
            printf("liuj: wait_count=%d, wait_time=%u\n",wait_count,wait_time);
            thread_manage_wait(thread, wait_time);
            wait_count ++;
        }
    }

    return NULL;
}

#if 1
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
    pthread_detach(tid);  //1. 不阻塞，线程独立运行
    //pthread_join(tid,&ret); //2. 阻塞，直到子线程结束， **ret保持线程返回值

    char cmd[16];
    while(1)
    {
        printf("please inpud cmd: s-stop r-runing\n");
        scanf("%s",cmd);
        if(cmd[0] == 'r')
        {
            thread_manage_wakeup(&wan_judge_thread);\
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