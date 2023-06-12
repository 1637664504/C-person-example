#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <signal.h>
#include <sys/syscall.h>

int thread_ret;
struct _info{
    int val;
}info;

void handler_signal(int signal)
{
    printf("sig=%d \n",signal);
}

int init_signal()
{
    struct sigaction act;
    act.sa_handler = handler_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGUSR1,&act,0);
    //sigaction(SIGINT,&act,0);
}

pid_t gettid()
{
	return syscall(SYS_gettid);
}

void *thread_handler(void *ptr)
{
    int i;
    init_signal();

    for(i=0;i<50;i++){
        sleep(5);
        printf("thread_handler i=%d tid=%u +++++\n",i,gettid());
    }

    thread_ret=2200;
    pthread_exit(&thread_ret);
}

int create_pthread(void)
{
    pthread_t tid;
    void *ret;
    int status = pthread_create(&tid, NULL, thread_handler, NULL);
    if(status != 0)
    {
        perror("pthread_create error");
    }
    pthread_detach(tid);  //1. 不阻塞，线程独立运行
    //pthread_join(tid,&ret); //2. 阻塞，直到子线程结束， **ret保持线程返回值
    //printf("main thread over----ret=%d\n",*(int *)ret);

    for(int i=0;i<50;i++){
        sleep(1);
        //printf("main thread %d----\n",i);
    }
    return tid;
}



int main ( int argc, char *argv[] )
{
    //init_signal();
    create_pthread();

    return 0;
}