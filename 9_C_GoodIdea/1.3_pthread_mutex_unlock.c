/*
实现：生产/消费模型
信号量实现
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<pthread.h>
#include<semaphore.h>

pthread_mutex_t q_lock;

#define sys_lock(lock) pthread_mutex_lock(lock)
#define sys_unlock(lock) pthread_mutex_unlock(lock)

void* producer(void *arg)
{
    int count =5;
    printf("in %s \n",__func__);
    
    while(count --){
        sys_lock(&q_lock);
        printf("++++++ %d\n",count);
        sys_unlock(&q_lock);
        sleep(3);
    }
    pthread_exit(NULL);
}

void* consumer(void *arg)
{
    int count =5;
    printf("in %s \n",__func__);
    
    while(count --){
        sys_lock(&q_lock);
        printf("----- %d\n",count);
        sys_unlock(&q_lock);
        sleep(2);
    }
    pthread_exit(NULL);
}

int main(int argc,char *argv[])
{
    pthread_t tid1, tid2,tid3;
    int ret;
    void *pthread_ret;

    ret = pthread_mutex_init(&q_lock,NULL);

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
    printf("all pthread end\n");
    pthread_mutex_destroy(&q_lock);
    //sem_destroy(&c_lock);

    return 0;
}

/* result:

in consumer
----- 4
in producer
++++++ 4
----- 3
++++++ 3
----- 2
++++++ 2
----- 1
----- 0
++++++ 1
++++++ 0
all pthread end



*/



