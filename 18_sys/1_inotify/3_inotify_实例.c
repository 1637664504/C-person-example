/*
意图:
1. odhcp6c -s dhcpv6.script 
脚本dhcpv6.script会将 ipv6的 address,getway,dns写入到文件/tmp/ipv6_info 中

2.监听文件 /tmp/ipv6_info IN_CLOSE_WAIT(写结束事件)

*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/inotify.h>

//#define JRD_IPV6_INFO_FILE "/tmp/ipv6_info"
#define JRD_IPV6_INFO_FILE "ipv6_info"

struct inotify_info{
    uint32_t mask;
    char event_name[16];
};

struct inotify_info inotify_list[15]={
    {IN_ACCESS,"IN_ACCESS"},
    {IN_MODIFY,"IN_MODIFY"},
    {IN_ATTRIB,"IN_ATTRIB"},
    {IN_CLOSE_WRITE,"IN_CLOSE_WRITE"},
    {IN_CLOSE_NOWRITE,"IN_CLOSE_NOWRITE"},
    //to do
};

void inotify_show_info(uint32_t mask)
{
    char buf[64];
    memset(buf,0,sizeof(buf));
    int list_size = sizeof(inotify_list)/sizeof(inotify_list[0]);
    int i;

    for(i=0;i<list_size;i++){
        if(inotify_list[i].mask & mask)
        {
            strcat(buf,inotify_list[i].event_name);
            break;
        }
    }

    printf("event=%s\n",buf);
}

void update_ipv6_info(void)
{
    FILE *fp;
    fp = fopen(JRD_IPV6_INFO_FILE,"r");
    if(!fp){
        perror("fopen fail");
        return;
    }

    char buf[256];
    while(fgets(buf,sizeof(buf)-1,fp)){
        printf("buf=%s\n",buf);
    }

    fclose(fp);

}

int main(int argc,char *argv[])
{
    int notify_fd;
    notify_fd = inotify_init();
    if(notify_fd == -1)
    {
        perror("inotify_init fail");
        exit(-1);
    }

    int len,event_len;
    char buf[256];
    char *p;
    struct inotify_event *event;
    int testFile_wd = 0;
    event_len = sizeof(struct inotify_event);

    testFile_wd = inotify_add_watch(notify_fd,JRD_IPV6_INFO_FILE,IN_CLOSE_WRITE);
    if(testFile_wd < 0){
        perror("inotify_add_watch file fail");
        exit(-2);
    }

    while(1){
        memset(buf,0,sizeof(buf));
        p = buf;
        len = read(notify_fd,buf,sizeof(buf)-1);
        while(len > 0)
        {
            event=(struct inotify_event *)p;
            printf("event wd:%d mask:%u cookie=%u len=%u name=%s\n",event->wd,event->mask,event->cookie,event->len,event->name);
            if(testFile_wd == event->wd)
            {
                printf("file %s--",JRD_IPV6_INFO_FILE);
                inotify_show_info(event->mask);
            }

            p = (&(event->name[0])+event->len);
            len -= (event_len+event->len);
        }

        update_ipv6_info();
    }

    close(notify_fd);

    return 0;
}

/*
测试:
./a.out &
echo 111 > ipv6_info
echo 222 > ipv6_info
echo 111 > ipv6_info

*/