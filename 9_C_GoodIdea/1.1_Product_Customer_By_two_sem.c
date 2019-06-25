/*
实现：生产/消费模型
两个信号量实现
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<pthread.h>
#include<semaphore.h>

sem_t q_lock;
sem_t c_lock;

void sys_lock(sem_t *lock)
{
    sem_wait(lock);
}
void sys_unlock(sem_t *lock)
{
    sem_post(lock);
}

void* producer(void *arg)
{
    int count =5;
    printf("in %s \n",__func__);
    
    while(count --){
        sys_lock(&q_lock);
        printf("++++++ %d\n",count);
        sleep(1);
        sys_unlock(&c_lock);
    }
    pthread_exit(NULL);
}

void* consumer(void *arg)
{
    int count =5;
    printf("in %s \n",__func__);
    
    while(count --){
        sys_lock(&c_lock);
        printf("----- %d\n",count);
        sleep(2);
        sys_unlock(&q_lock);
    }
    pthread_exit(NULL);
}

int main(int argc,char *argv[])
{
    pthread_t tid1, tid2,tid3;
    int ret;
    void *pthread_ret;

    ret = sem_init(&q_lock,0,1);
    ret = sem_init(&c_lock,0,0);
    if(ret < 0){
        perror("sem_init error");
        exit(-1);
    }
    pthread_create(&tid1, NULL, (void *)producer, NULL);
    pthread_create(&tid2, NULL, (void *)consumer, NULL);
    //pthread_create(&tid3, NULL, (void *)consumer2, NULL);
    pthread_join(tid1,&pthread_ret);
    pthread_join(tid2,&pthread_ret);
    //pthread_join(tid3,&pthread_ret);
    sem_destroy(&q_lock);
    sem_destroy(&c_lock);

    return 0;
}

/* result:

in producer
++++++ 4
in consumer
----- 4
++++++ 3
----- 3
++++++ 2
----- 2
++++++ 1
----- 1
++++++ 0
----- 0

按顺序执行
*/


