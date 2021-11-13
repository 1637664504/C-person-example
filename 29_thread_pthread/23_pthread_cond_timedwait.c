#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int thread_ret;
static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t g_cond = PTHREAD_COND_INITIALIZER;

void *thread_handler(void *ptr)
{
    struct timespec abstime;
    int ret;

    memset(&abstime,0,sizeof(abstime));
    abstime.tv_sec = time(NULL) + 5;
    printf("thread 11111111 +++++++\n");
    //pthread_cond_wait(&g_cond, &g_mutex);         //1.一直等待
    ret = pthread_cond_timedwait(&g_cond, &g_mutex, &abstime);  //2.超时5s 推出
    pthread_mutex_unlock(&g_mutex);
    if(ret == ETIMEDOUT)
    {
        
    }
    printf("thread 22222222 +++++++\n");
    
}

int create_pthread(void)
{
    pthread_t tid;
    
    void *ret;

    pthread_mutex_lock(&g_mutex);
    int status = pthread_create(&tid, NULL, thread_handler, NULL);
    if(status != 0)
    {
        perror("pthread_create error");
    }
    pthread_detach(tid);  //1. 不阻塞，线程独立运行
    //pthread_join(tid,&ret); //2. 阻塞，直到子线程结束， **ret保持线程返回值
    printf("main thread ----\n");
    for(int i=0;i<2;i++){
        sleep(1);
        printf("main thread %d----\n",i);
    }
    pthread_cond_broadcast(&g_cond);
    //sleep(10);
    return tid;
}

int main ( int argc, char *argv[] )
{
    create_pthread();

    return 0;
}

/*
结果:
    create_pthread();
    create_pthread();   //运行第二个 子线程时，需要等待 mutex 解锁
*/