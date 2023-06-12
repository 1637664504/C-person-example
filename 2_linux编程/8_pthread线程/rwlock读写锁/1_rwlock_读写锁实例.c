#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

pthread_rwlock_t rwlock;
void *thread_read(void *arg)
{
    //int i=*((int *)arg);
    int i = (int)arg;

    pthread_rwlock_rdlock(&rwlock);
    printf("i=%d,rwlock time=%lu +++\n",i,time(NULL));
    sleep(4);
    pthread_rwlock_unlock(&rwlock);
    printf("i=%d,rw unlock ---\n",i);

    return NULL;
}

void *thread_write(void *arg)
{
    //int i=*((int *)arg);
    int i = (int)arg;

    pthread_rwlock_wrlock(&rwlock);
    printf("i=%d,wrlock time=%lu +++\n",i,time(NULL));
    sleep(4);
    pthread_rwlock_unlock(&rwlock);
    printf("i=%d,wr unlock ---\n",i);

    return NULL;
}

int main(void)
{
	int i;
	pthread_t tid[4];

	pthread_rwlock_init(&rwlock,NULL);
	for(i=0;i<2;i++)
	    pthread_create(&tid[i],NULL,thread_read,(void *)i);
	for(i=2;i<4;i++)
	    pthread_create(&tid[i],NULL,thread_write,(void *)i);
	for(i=0;i<4;i++)
	    pthread_join(tid[i],NULL);
    pthread_rwlock_destroy(&rwlock);

	return 0;
}

/*
功能测试
rwlock
rwlock
wrlock
wrlock

测试结果
i=0,rwlock time=1662282574 +++
i=1,rwlock time=1662282574 +++
i=1,rw unlock ---
i=0,rw unlock ---
i=2,wrlock time=1662282578 +++
i=2,wr unlock ---
i=3,wrlock time=1662282582 +++
i=3,wr unlock ---

测试结论:
读锁无阻塞
写锁会阻塞

*/