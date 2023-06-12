#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

pthread_rwlock_t rwlock;
void *thread_read(void *arg)
{
    //int i=*((int *)arg);
    int i = (int)arg;
	//保证 写线程 先执行
	//sleep(1);

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
	pthread_t tid[2];

	pthread_rwlock_init(&rwlock,NULL);
	    pthread_create(&tid[0],NULL,thread_write,(void *)0);
		sleep(1);	//保证 写线程 先执行
	    pthread_create(&tid[1],NULL,thread_read,(void *)1);

	for(i=0;i<2;i++)
	    pthread_join(tid[i],NULL);
    pthread_rwlock_destroy(&rwlock);

	return 0;
}

/*
功能测试: 写 读
wrlock
rwlock

测试结果
		--> 写 读
i=0,wrlock time=1662283889 +++
i=0,wr unlock ---
i=1,rwlock time=1662283893 +++
i=1,rw unlock ---


、
测试结论:
写锁获取期间，
	读锁阻塞

*/