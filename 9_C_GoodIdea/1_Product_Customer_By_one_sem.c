/*
实现：生产/消费模型
信号量实现
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<pthread.h>
#include<semaphore.h>

sem_t sem_lock;
void* producer(void *arg)
{
    int count =5;
    printf("in %s \n",__func__);
    
    while(count --){
        sem_post(&sem_lock);
        printf("++++++ %d\n",count);
        sleep(1);
        sem_wait(&sem_lock);
    }
    pthread_exit(NULL);
}

void* consumer(void *arg)
{
    int count =5;
    printf("in %s \n",__func__);
    
    while(count --){
        sem_post(&sem_lock);
        printf("----- %d\n",count);
        sleep(2);
        sem_wait(&sem_lock);
    }
    pthread_exit(NULL);
}


int main(int argc,char *argv[])
{
    pthread_t tid1, tid2;
    int ret;
    void *pthread_ret;

    ret = sem_init(&sem_lock,0,0);
    if(ret < 0){
        perror("sem_init error");
        exit(-1);
    }
    pthread_create(&tid1, NULL, (void *)producer, NULL);
    pthread_create(&tid2, NULL, (void *)consumer, NULL);
    pthread_join(tid1,&pthread_ret);
    pthread_join(tid2,&pthread_ret);
    sem_destroy(&sem_lock);

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
++++++ 1
----- 2
++++++ 0
----- 1
----- 0

*/
