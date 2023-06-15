/*
参考:
https://blog.csdn.net/ThinPikachu/article/details/102922701


p操作：当信号量值为0时，进程阻塞；当信号量值大于0时，信号量减1，进程获得资源继续运行。
v操作：将信号量值加1，不会发生阻塞，v操作代表释放资源

 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

#include "common.h"

void sem_p_lock(int semid)
{
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = SEM_UNDO;
    if (semop(semid, &buf, 1) == -1)
        perror("semop p_lock failed");

}

void sem_v_unlock(int semid)
{
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = SEM_UNDO;
    if (semop(semid, &buf, 1) == -1)
        perror("semop p_lock failed");

}

void sem_release(int semid)
{
    if (semctl(semid, 0, IPC_RMID) == -1)
        perror("semctl rm failed");
}

int main(void)
{
    system("touch /var/tmp/sem_test");
    
    int key = ftok(SEM_TEST_PATH, 1);
    int semid;
    semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1)
    {
        perror("semget failed");
        return -1;
    }

    union semun a;
    a.val = 1;
    if (semctl(semid, 0, SETVAL, a) == -1)
    {
        perror("semctl set val failed");
    }

    sem_p_lock(semid);
    sem_v_unlock(semid);
    sem_release(semid);

    return 0;
}