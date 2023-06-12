#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/inotify.h>

const char *testAFile = "a.txt";
const char *testBFile = "b.txt";

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
            strcat(buf,inotify_list[i].event_name);
    }

    printf("event=%s\n",buf);
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
    int testAFile_wd = 0;
    int testBFile_wd = 0;
    event_len = sizeof(struct inotify_event);

    testAFile_wd = inotify_add_watch(notify_fd,testAFile,IN_CLOSE_WRITE);
    testBFile_wd = inotify_add_watch(notify_fd,testBFile,IN_CLOSE_WRITE);
    if(testAFile_wd < 0 || testBFile_wd < 0){
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
            if(testAFile_wd == event->wd)
            {
                printf("file %s--",testAFile);
                inotify_show_info(event->mask);
            }
            else if(testBFile_wd == event->wd)
            {
                printf("file %s--",testBFile);
                inotify_show_info(event->mask);
            }

            p = (&(event->name[0])+event->len);
            len -= (event_len+event->len);
        }
    }

    close(notify_fd);
    return 0;
}
