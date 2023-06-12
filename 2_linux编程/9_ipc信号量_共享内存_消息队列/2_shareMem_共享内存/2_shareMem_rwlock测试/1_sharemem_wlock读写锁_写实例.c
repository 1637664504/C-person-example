#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

pthread_rwlock_t *rwlock;

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
            pthread_rwlock_wrlock(rwlock);
            printf("加wlock\n");
        }
        else if (cmd == 'r')
        {
            pthread_rwlock_rdlock(rwlock);
            printf("加rlock\n");
        }
        else if (cmd == 'c')
        {
            pthread_rwlock_unlock(rwlock);
            printf("解锁\n");
        }
    }

    return NULL;
}

int sharemem_rwlock_init(pthread_rwlock_t **lock)
{
    int shm_id;
    void* shm_p = NULL;
    shm_id = shmget(KEY_SHAREMEM,SHAREMEM_SIZE,0644|IPC_CREAT);
    if(shm_id == -1){
        printf("shmget failed: %s",strerror(errno));
        exit(-1);
    }
    shm_p = shmat(shm_id,NULL,0);
    *lock=(pthread_rwlock_t *)shm_p;

    return 0;
}

void sharemem_rwlock_release(void *ptr)
{
    if(shmdt(ptr) == -1){
        printf("shmat failed %s\n",strerror(errno));
        exit(-1);
    }
}

int main(void)
{
    int num = 3;
    pthread_t tid;
    
    sharemem_rwlock_init(&rwlock);

    pthread_rwlock_init(rwlock, NULL);
    pthread_create(&tid, NULL, thread_write_cmd, (void*)&num);
    pthread_join(tid, NULL);
    pthread_rwlock_destroy(rwlock);

    sharemem_rwlock_release(rwlock);

    return 0;
}
/*

 */