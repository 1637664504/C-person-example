#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/inotify.h>

const char *testFile = "1.txt";
int main(int argc,char *argv[])
{
    int notify_fd;
    notify_fd = inotify_init();
    if(notify_fd == -1)
    {
        perror("inotify_init fail");
        exit(-1);
    }

    int testFile_fd;
    testFile_fd = inotify_add_watch(notify_fd,testFile,IN_CLOSE_WRITE);
    if(testFile_fd < 0){
        perror("inotify_add_watch file fail");
        exit(-2);
    }

    int len,event_len;
    char buf[1024];
    char *p = buf;
    struct inotify_event *event;
    len = read(notify_fd,buf,sizeof(buf)-1);
    event_len = sizeof(struct inotify_event);

    while(len > 0)
    {
        event=(struct inotify_event *)p;
        printf("event wd:%d mask:%u cookie=%u len=%uname: %s\n",event->wd,event->mask,event->cookie,event->len,event->name);
        p = (&(event->name[0])+event->len);
        len -= (event_len+event->len);
    }

    close(notify_fd);
    return 0;
}
