#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>

int main ( int argc, char *argv[] )
{
    int fd=0;
    int notify_num=0;
    struct inotify_event event;

    fd = inotify_init();    //1.监听初始化 返回一个监听文件描述符
    //2.监听文件, 与监听事件:被打开,被修改
    //  返回一个监听描述符(可以理解为监听 num)
    notify_num = inotify_add_watch(fd,"test.txt",IN_ACCESS|IN_MODIFY|IN_ATTRIB|IN_OPEN);
    memset(&event,0,sizeof(event));

    //3.read() 读取 inotify_event 事件
    while(read(fd,&event,sizeof(event))){
        printf("read event:num=%d  mask=%x name=%s\n",
            event.wd,
            event.mask,
            event.name);
    }

    return 0;
}

