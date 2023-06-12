/*
官方文档示例:
通过判断条件变量 x,y 
    来实现线程的 等待、唤醒动作
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int x,y;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread_handler(void *ptr)
{
    printf("thread 11111111 +++++++\n");
    pthread_mutex_lock(&mut);
    while (x <= y) {
            pthread_cond_wait(&cond, &mut);
    }
    /* operate on x and y */
    pthread_mutex_unlock(&mut);
    printf("thread 22222222 +++++++\n");
    
}

void *thread_handler_test(void *ptr)
{
    printf("thread_handler_test\n");
    for(int i=0;i<5;i++){
        sleep(1);
        printf("main thread %d----\n",i);
    }

    pthread_mutex_lock(&mut);
    /* modify x and y */
    x = 9;
    //if (x > y) pthread_cond_broadcast(&cond);
    printf("----------- signal\n");
    if (x > y) pthread_cond_signal(&cond);
    printf("----------- signal after\n");
    pthread_mutex_unlock(&mut);
}

int create_pthread(void)
{
    pthread_t tid;
    pthread_t test;
    void *ret;

    //1.初始化条件变量
    x = 5;
    y = 7;

    int status = pthread_create(&tid, NULL, thread_handler, NULL);
    if(status != 0)
    {
        perror("pthread_create error");
    }
    pthread_join(tid,&ret);  //1. 不阻塞，线程独立运行
    //pthread_join(tid,&ret); //2. 阻塞，直到子线程结束， **ret保持线程返回值

    status = pthread_create(&test, NULL, thread_handler_test, NULL);
    pthread_join(test, &ret);




    sleep(10);

    return tid;
}

int main ( int argc, char *argv[] )
{
    create_pthread();

    return 0;
}

/*
结果:

*/