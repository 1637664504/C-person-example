#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include "common.h"

pthread_rwlock_t *rwlock;
void* thread_read(void* arg)
{
    int id = *(int*)arg;
    while (1)
    {
        printf("id=%d 1:try rlock\n", id);
        pthread_rwlock_rdlock(&rwlock);
        printf("id=%d 2:get rlock\n", id);

        sleep(2);
        pthread_rwlock_unlock(&rwlock);
        printf("id=%d 3:unlock ---\n", id);
        sleep(4);
    }

    return NULL;
}

void* thread_write(void* arg)
{
    int id = *(int *)arg;

    while(1)
    {
        printf("id=%d,wrlock time=%lu +++\n", id, time(NULL));
        pthread_rwlock_wrlock(&rwlock);
        sleep(2);
        pthread_rwlock_unlock(&rwlock);
        printf("id=%d,wr unlock ---\n", id);
        sleep(2);
    }

    return NULL;
}

void* thread_write_cmd(void* arg)
{
    // int id = *(int *)arg;

    char cmd;
    while ((cmd = getchar()))
    {
        if (cmd == 'q')
            break;
        else if (cmd == 'w')
        {
            pthread_rwlock_wrlock(&rwlock);
            printf("加wlock\n");
        }
        else if (cmd == 'r')
        {
            pthread_rwlock_rdlock(&rwlock);
            printf("加rlock\n");
        }
        else if (cmd == 'c')
        {
            pthread_rwlock_unlock(&rwlock);
            printf("解锁\n");
        }
    }

    return NULL;
}

int main(void)
{
    int num[4] = { 1, 2, 3, 4 };
    pthread_t tid[4];

    pthread_rwlock_init(&rwlock, NULL);
    pthread_create(&tid[0], NULL, thread_read, (void*)&num[0]);
    pthread_create(&tid[1], NULL, thread_read, (void*)&num[1]);
    // pthread_create(&tid[2], NULL, thread_write, (void*)&num[2]);
    pthread_create(&tid[3], NULL, thread_write_cmd, (void*)&num[3]);

    for (int i = 0;i < 4;i++)
        pthread_join(tid[i], NULL);
    pthread_rwlock_destroy(&rwlock);

    return 0;
}
/*
1.读验证~~~~~~~~~~~~~~~~~~~~~~~~~
r
加rlock
id=2 1:try rlock
id=2 2:get rlock
id=1 1:try rlock
id=1 2:get rlock

结果:
rlock不阻塞

2.写锁测试~~~~~~~~~~~~~~~~~~~~~~~~~
w
加wlock
id=2 1:try rlock
id=1 1:try rlock
... 一直阻塞
c
解锁
id=2 2:get rlock
id=1 2:get rlock
id=2 3:unlock ---
id=1 3:unlock ---

结论:
wlock 阻塞rlock, wlock

 */