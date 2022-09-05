#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

typedef enum {
	e_rwlock_write = -1,
	e_rwlock_non = 0,
	e_rwlock_read,
} e_rwlock_state;

struct rwlock{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int state;
}testLock;

void rwlock_init(struct rwlock *lock)
{
	pthread_mutex_init(&lock->mutex,NULL);
	pthread_cond_init(&lock->cond,NULL);
	lock->state = e_rwlock_non;
}

void rlock(struct rwlock *lock)
{
	pthread_mutex_lock(&lock->mutex);
	while(lock->state < e_rwlock_non)
		pthread_cond_wait(&lock->cond, &lock->mutex);
	
	lock->state++;
	pthread_mutex_unlock(&lock->mutex);
}

void runlock(struct rwlock *lock)
{
	pthread_mutex_lock(&lock->mutex);
	lock->state--;
	pthread_cond_signal(&lock->cond);
	pthread_mutex_unlock(&lock->mutex);
}

void wlock(struct rwlock *lock)
{
	pthread_mutex_lock(&lock->mutex);
	while(lock->state != e_rwlock_non)
		pthread_cond_wait(&lock->cond, &lock->mutex);
	
	lock->state = e_rwlock_write;
	pthread_mutex_unlock(&lock->mutex);
}

void wunlock(struct rwlock *lock)
{
	pthread_mutex_lock(&lock->mutex);
	lock->state = e_rwlock_non;
	pthread_cond_broadcast(&lock->cond);
	pthread_mutex_unlock(&lock->mutex);
}

void *thread_read(void *arg)
{
    int i=*((int *)arg);
	sleep(1);
	printf("read begin: i=%d ~~~\n",i);
    rlock(&testLock);
    printf("read mid: i=%d,rwlock time=%lu +++\n",i,time(NULL));
    sleep(4);
    runlock(&testLock);
    printf("read end:i=%d unlock ---\n",i);

    return NULL;
}

void *thread_write(void *arg)
{
    int i=*((int *)arg);
	printf("write begin: i=%d ~~~\n",i);

    wlock(&testLock);
    printf("write mid:i=%d,rwlock time=%lu +++\n",i,time(NULL));
    sleep(4);
    wunlock(&testLock);
    printf("write end:i=%d unlock ---\n",i);

    return NULL;
}

int main(void)
{
	int a[4]={0,1,2,3};
	pthread_t tid[4];

	rwlock_init(&testLock);
	pthread_create(&tid[0],NULL,thread_read,&a[0]);
	pthread_create(&tid[1],NULL,thread_read,&a[1]);
	pthread_create(&tid[2],NULL,thread_write,&a[2]);
	pthread_create(&tid[3],NULL,thread_write,&a[3]);
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	pthread_join(tid[2],NULL);
	pthread_join(tid[3],NULL);

	return 0;
}

/*
测试1:
读 读 写
结果
读 -->不阻塞
读 -->不阻塞
写 -->等等唤醒

测试2:
写 读 读
预期结果:
写 期间，读阻塞
写完成，读读不阻塞


*/