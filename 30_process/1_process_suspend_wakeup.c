#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/syscall.h>

int thread_ret;
pid_t thread_pid1;

int suspend(pid_t pid)
{
    return kill(pid,SIGSTOP);
}

int wakeup(pid_t pid)
{
    return kill(pid,SIGCONT);
}

unsigned int get_thread_pid()
{
    return syscall(SYS_gettid);
}

void *thread_handler(void *ptr)
{
    int i;
    char *id = (char *)ptr;
    thread_pid1 = get_thread_pid();

    for(i=0;i<5;i++){
        sleep(1);
        printf("id:%s pid=%u tid=%u ttid=%u\n", id, getpid(),pthread_self(),get_thread_pid());
    }

    thread_ret=2200;
    pthread_exit(&thread_ret);
}

int create_pthread(void)
{
    pthread_t pid1,pid2;
    void *ret;
    int status;


    status = pthread_create(&pid1, NULL, thread_handler, "aaa");
    if(status != 0)
    {
        perror("pthread_create error");
    }
    printf("pid1=%u\n",pid1);
    pthread_detach(pid1);  //1. 不阻塞，线程独立运行

#if 0
    status = pthread_create(&pid2, NULL, thread_handler, "bbb");
    if(status != 0)
    {
        perror("pthread_create error");
    }
    printf("pid2=%u\n",pid2);
    pthread_detach(pid2);  //1. 不阻塞，线程独立运行
#endif
    //printf("main thread over----ret=%d\n",*(int *)ret);

    for(int i=0;i<50;i++){
        sleep(1);
        if(i%3)
        {
            printf("suspend \n");
            suspend(thread_pid1);
        }
        else if(i%3 == 1)
        {
            printf("wakeup \n");
            wakeup(thread_pid1);
        }
        printf("main thread %d----\n",i);
    }
    return 0;
}

int main ( int argc, char *argv[] )
{
    create_pthread();

    return 0;
}