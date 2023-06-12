#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdint.h>
#include <string.h>
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

int mmap_rwlock_init(pthread_rwlock_t **lock)
{
    int fd = 0;
    char *ptr = NULL;
 
    if ((fd = open(MMAP_FILE, O_RDWR)) < 0)
    {
        perror("open file error\n");
        return -1;
    }

    // 映射文件大小不能为空
    // 方案1: write(fd, "1", 1);
    // 方案2
    ftruncate(fd, 64);
    
    ptr = (char*)mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED)
    {
        printf("mmap failed\n");
        close(fd);
        return -1;
    }
    *lock = (pthread_rwlock_t *)ptr;

    return 0;
}

void mmap_rwlock_release(void *ptr)
{
    munmap(ptr, PAGE_SIZE);
}

int main(void)
{
    int num[4] = { 1, 2, 3, 4 };
    pthread_t tid[4];

    mmap_rwlock_init(&rwlock);
    
    pthread_rwlock_init(rwlock, NULL);
    pthread_create(&tid[3], NULL, thread_write_cmd, (void*)&num[3]);
    pthread_join(tid[3], NULL);
    pthread_rwlock_destroy(rwlock);

    mmap_rwlock_release(rwlock);

    return 0;
}
/*
1.wlock 写锁验证~~~~~~~~~~~~~~~~~~~~~~~~~

id=3 1:try rlock
-->释放锁, 无法进行到下一步

 */