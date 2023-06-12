#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#define IPV4_ADDRESS_LEN 16
#define IPV6_ADDRESS_LEN 40
#define MAC_LEN 18

typedef enum internet_status{
    INTERNET_INVALID = 0,
    INTERNET_ok,    
}E_INTERNET_STATUS;

typedef enum link_status{
    LINK_INVALID = 0,
    LINK_UP,
    LINK_DOWN,
    LOWER_UP,
}E_LINK_STATUS;

typedef enum network_status{
    NETWORK_INVALID = 0,
    NETWORK_DISCONNECT,
    NETWORK_CONNECTTING,
    NETWORK_CONNECTED,
}E_NETWORK_STATUS;

typedef struct {
    char ifname[16];
    char mac[MAC_LEN];
    E_LINK_STATUS status;
    unsigned int mtu;
    unsigned int proto;
    //struct usage_stats stats;
}Net_link;

struct wan_interface_status{
    char ifname[16]; 
    //E_NETWORK_STATUS network_status;
    //unsigned internet_status;
    unsigned int metric;
    pthread_mutex_t mut ;
    pthread_cond_t cond ;
}wan, wwan;



int system_cmd_call_get_exit_code(const char *cmd)
{
    int ret,status,finish,exit_code;

    ret = system(cmd);
    if(ret==0)
    {
        return 0;
    }
    else if(ret == -1)
    {
        return -1;
    }
    else
    {
        printf("ret=%d ,err=%s\n",ret,strerror(errno));
        if(WIFEXITED(status)){
            finish= WIFEXITED(status);
            exit_code = WEXITSTATUS(status);
            printf("cmd exit with %d. Finish=%d\n", exit_code,finish);
        }
        else if (WIFSIGNALED(status))
        {
                int if_finished_by_signal,signal_code;
                if_finished_by_signal = WIFSIGNALED(status);
                signal_code = WTERMSIG(status);
                printf( "signal_code is %d\n", signal_code);
        }
        else if (WIFSTOPPED(status))
        {
                int if_stoped,stop_signal_code;
                if_stoped = WIFSTOPPED(status);
                stop_signal_code = WSTOPSIG(status);
                printf( "stop_signal_code is %d\n", stop_signal_code);
        }
    }

    return ret;
}

char test_ip[3][IPV4_ADDRESS_LEN]={
    "223.5.5.5",
    "8.8.8.8",
    "8.8.4.4"
};



void *thread_handler(void *ptr)
{
    int sleep_time = 2;
    struct wan_interface_status *wan;
    int idx=0;

    if(ptr)
        wan = (struct wan_interface_status *)ptr;

    if(strcmp(wan->ifname,"eth1") == 0)
        idx = 111;
    else
        idx = 222;

    printf("%d: ifname=%s wan=%p\n",idx,wan->ifname, wan);
    #if 1
    while(1)
    {
        pthread_mutex_lock(&wan->mut);
        while (wan->network_status != NETWORK_CONNECTED) {
                printf("%d:----------------------- =%d, st=%p\n",idx,wan->network_status, &wan->network_status);
                pthread_cond_wait(&wan->cond, &wan->mut);
        }

        int i=0;
        for(i=0; i<3; i++)
        {
            char cmd[128] = {0};
            int ret;
                snprintf(cmd,sizeof(cmd)-1,"ping -I %s -W 8 -c 3 %s",wan->ifname,test_ip[i]);
                ret = system_cmd_call_get_exit_code(cmd);
                if(ret == 0)
                {
                    wan->internet_status ++;
                    wan->metric -=2 ;
                    break;
                }
        }
        printf("%d: internet=%u, metric=%u\n",idx, wan->internet_status,wan->metric);

        if(wan->internet_status)
        {
            //set ro/dns/firewall
            //dns 需要冲裁
            if(sleep_time < 32)
                sleep_time = sleep_time << 1;
        }
        else
        {
            //reset ro --> 修改 metric, 默认值50,51
            //firewall NAT --> 受默认路由影响，不做修改
            //clean dns --> dns影响上网功能，不可以上网则删除

            sleep_time = 2;
        }
        //3.重置 metric
        wan->internet_status = 0;
        wan->metric =  DEFAULT_PRIMARY_METRIC;

        struct timespec wait_time = {0};
        wait_time.tv_sec = time(NULL) + sleep_time;
        pthread_cond_timedwait(&wan->cond, &wan->mut, &wait_time);
        pthread_mutex_unlock(&wan->mut);
    }
    #endif
}

void wake_up_wan_ping_thread(void)
{
    pthread_mutex_lock(&wan.mut);
    pthread_cond_signal(&wan.cond);
    pthread_mutex_unlock(&wan.mut);
}

void wake_up_wwan_ping_thread(void)
{
    pthread_mutex_lock(&wwan.mut);
    pthread_cond_signal(&wwan.cond);
    pthread_mutex_unlock(&wwan.mut);
}

void ping_thread()
{
    memset(&wan,0,sizeof(wan));
    strcpy(wan.ifname,"eth1");
    wan.metric = DEFAULT_PRIMARY_METRIC;
    wan.network_status = NETWORK_CONNECTED;
    pthread_mutex_init(&wan.mut,NULL);
    pthread_cond_init(&wan.cond,NULL);

    memset(&wwan,0,sizeof(wwan));
    strcpy(wwan.ifname,"eth2");
    wwan.metric = DEFAULT_BACKUP_METRIC;
    wwan.network_status = NETWORK_CONNECTED;
    pthread_mutex_init(&wwan.mut,NULL);
    pthread_cond_init(&wwan.cond,NULL);

    pthread_t pid_wan, wan_test;
    pthread_t pid_wwan;
    int status;
    void *ret,*ret2;

    #if 0
    status = pthread_create(&pid_wan, NULL, thread_handler, &wan);
    if(status != 0)
        perror("pthread_create 11 error");
    pthread_detach(wan_test);
    #endif
    
    status = pthread_create(&pid_wwan, NULL, thread_handler, &wwan);
    if(status != 0)
        perror("pthread_create 11 error");
    
    pthread_join(pid_wwan,&ret);

}

int main(int argc, char *argv[])
{
    ping_thread();

    return 0;
}