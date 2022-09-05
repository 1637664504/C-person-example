#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lock;
pthread_cond_t cond;
void *thread_read(void *arg)
{
    int i=*((int *)arg);

	printf("read start i=%d\n",i);
    pthread_mutex_lock(&lock);
	pthread_cond_wait(&cond,&lock);
    printf("read i=%u,lock time=%lu +++\n",i,time(NULL));
    pthread_mutex_unlock(&lock);
    printf("read end i=%d,rw unlock ---\n",i);

    return NULL;
}

void *thread_write(void *arg)
{
    int i=*((int *)arg);

	sleep(1);
	printf("write start i=%d\n",i);
    pthread_mutex_lock(&lock);
	pthread_cond_broadcast(&cond);
    printf("write i=%u,lock time=%lu +++\n",i,time(NULL));
    pthread_mutex_unlock(&lock);
    printf("write end i=%d unlock ---\n",i);

    return NULL;
}

int main(void)
{
	int i;
	#define threadMaxNum 4
	int a[threadMaxNum]={0,1,2,3};
	pthread_t tid[threadMaxNum];

	pthread_mutex_init(&lock,NULL);
	pthread_cond_init(&cond,NULL);
	for(i=0;i<2;i++)
	    pthread_create(&tid[i],NULL,thread_read,&a[i]);
	for(i=2;i<3;i++)
	    pthread_create(&tid[i],NULL,thread_write,&a[i]);
	for(i=0;i<3;i++)
	    pthread_join(tid[i],NULL);
    pthread_mutex_destroy(&lock);

	return 0;
}

/*
测试结果:
read start i=0
read start i=1
write start i=2
write i=2,lock time=1662365769 +++
write end i=2 unlock ---
read i=1,lock time=1662365769 +++
read end i=1,rw unlock ---
read i=0,lock time=1662365769 +++
read end i=0,rw unlock ---

测试结论：
一个cond_broadcast 激活 2个cond_wait线程
即broadcast确实能够激活所有等待线程 

*/