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

void* thread_read(void* arg)
{
    int id = *(int*)arg;
    while (1)
    {
        printf("id=%d 1:try rlock\n", id);
        pthread_rwlock_rdlock(rwlock);
        printf("id=%d 2:get rlock\n", id);

        sleep(2);
        pthread_rwlock_unlock(rwlock);
        printf("id=%d 3:unlock ---\n", id);
        sleep(4);
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
    int num = 1;
    pthread_t tid;
    
    sharemem_rwlock_init(&rwlock);

    pthread_rwlock_init(rwlock, NULL);
    pthread_create(&tid, NULL, thread_read, (void*)&num);
    pthread_join(tid, NULL);
    pthread_rwlock_destroy(rwlock);

    sharemem_rwlock_release(rwlock);

    return 0;
}
/*

 */