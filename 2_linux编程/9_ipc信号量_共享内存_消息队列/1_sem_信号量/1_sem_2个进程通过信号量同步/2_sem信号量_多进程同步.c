/*
多线程同步

通过指令
    l lock
    u unlock
查看sem信号量同步效果
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>

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

void input_cmd(int semid)
{
    char cmd;
    while ((cmd = getchar()))
    {
        if (cmd == 'q')
            break;
        else if (cmd == 'l')
        {
            sem_p_lock(semid);
            printf("父进程 加锁lock\n");
        }
        else if (cmd == 'u')
        {
            sem_v_unlock(semid);
            printf("父进程 解锁unlock\n");
        }
    }

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

    int ret = fork();
    if (ret == 0)
    {
        while (1)
        {
            printf("子进程 try sem lock\n");
            sem_p_lock(semid);
            printf("子进程 get sem lock\n");
            sleep(5);
            sem_v_unlock(semid);
            printf("子进程 unlock sem \n");
            sleep(5);
        }
    }
    else
    {
        input_cmd(semid);
    }

    return 0;
}

/*
子进程 try sem lock
子进程 get sem lock
子进程 unlock sem 
                        l
                        父进程 加锁lock
子进程 try sem lock
                        u
                        父进程 解锁unlock
子进程 get sem lock

 */