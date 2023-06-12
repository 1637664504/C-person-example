#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "sys_thread.h"

void *thread_test(void *arg)
{
    struct thread_manage *thread_mg = (struct thread_manage *)arg;
    while(1)
    {
        if(thread_mg->state != thread_running)
        {
            thread_mg->suspend(thread_mg,0);
        }

    }
}

void usage_show(void)
{
    char *p="
r : run thread
s : stop thread
d : destory thread and exit
    "
}

int main(void)
{

    struct thread_manage thread_mg;
    pthread_t pid;
    int ret;

    thread_mg.init(&thread_mg,thread_test);
    ret = pthread_create(&pid,NULL,thread_handler,(void *)&thread_mg);
    if(ret)
        perror("pthread_create fail");
    pthread_detach(pid);

    while(1)
    {
        
    }
}
