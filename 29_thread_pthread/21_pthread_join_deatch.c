#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int thread_ret;

void *thread_handler(void *ptr)
{
    int i;
    for(i=0;i<5;i++){
        sleep(1);
        printf("thread_handler %d +++++\n",i);
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
    //pthread_detach(tid);  //1. 不阻塞，线程独立运行
    pthread_join(tid,&ret); //2. 阻塞，直到子线程结束， **ret保持线程返回值
    printf("main thread over----ret=%d\n",*(int *)ret);

    for(int i=0;i<3;i++){
        sleep(1);
        printf("main thread %d----\n",i);
    }
    return tid;
}

int main ( int argc, char *argv[] )
{
    create_pthread();

    return 0;
}

/*

*/