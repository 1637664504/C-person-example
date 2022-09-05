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
	pthread_t tid[3];

	pthread_rwlock_init(&rwlock,NULL);
	    pthread_create(&tid[0],NULL,thread_read,(void *)0);
	    pthread_create(&tid[1],NULL,thread_write,(void *)1);
		pthread_create(&tid[2],NULL,thread_read,(void *)2);

	for(i=0;i<3;i++)
	    pthread_join(tid[i],NULL);
    pthread_rwlock_destroy(&rwlock);

	return 0;
}

/*
功能测试
rwlock
wrlock
rwlock

测试结果
		-->读 读 写
i=0,rwlock time=1662283342 +++
i=2,rwlock time=1662283342 +++
i=0,rw unlock ---
i=2,rw unlock ---
i=1,wrlock time=1662283346 +++


测试结论:
读阻塞期间，
	写锁挂起，读锁已经不阻塞。

*/