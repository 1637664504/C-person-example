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

int sem_wrok;

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


int* cake_num;
void* shm_p = NULL;
void product(int semid)
{
    while (1)
    {
        if (cake_num >= 0)
        {
            printf("店员: 没有客人\n");
            sleep(1);
            continue;
        }
        else
        {
            sem_p_lock(sem_work);
            {
                printf("店员: 来客人了, 开始做菜了\n");
                sem_v_unlock(semid);
                sleep(5);
                cake_num += 2;
                sem_p_unlock(semid);
            }
            sem_p_lock(sem_work);
        }
    }
}

void customer(int semid)
{
    char cmd;
    int num = 0;
    while ((cmd = getchar()))
    {
        printf("店员:请问你要多少个饼,请输入\n",num);
        if (cmd == 'q')
            break;
        else if (cmd > '0' && cmd <= '9')
        {
            cake_num = (int)(cmd - '0');
            // 唤醒生产者
            sem_v_unlock(sem_work);
            {
                printf("                        消费者: 我要%d个饼\n", num);
                while (cake_num)
                {
                    sem_p_lock(semid);
                    cake_num--;
                    sleep(2);
                    sem_v_unlock(semid);
                    printf("                    客人:%d 获得一个饼\n", cake_num);
                }
            }
            sem_p_lock(sem_work);
        }
    }
}

void sem_work_init(void)
{
    system("touch /var/tmp/sem_work");
    int key = ftok("/var/tmp/sem_work", 1);

    sem_work = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1)
    {
        perror("semget failed");
        return -1;
    }

    union semun a;
    a.val = 0;
    if (semctl(sem_work, 0, SETVAL, a) == -1)
    {
        perror("semctl set val failed");
    }
}

void shared_mem_init(void)
{
    int shm_id;
    int key = ftok("/var/tmp/sem_work", 1);

    shm_id = shmget(KEY, sizeof(int), 0644 | IPC_CREAT);
    if(shm_id == -1){
        printf("shmget failed: %s",strerror(errno));
        exit(-1);
    }
    shm_p = shmat(shm_id, NULL, 0);
    cake_num = (int*)shm_p;
}

void shared_mem_release(void)
{
    if(shmdt(shm_p) == -1){
        printf("shmat failed %s\n",strerror(errno));
        exit(-1);
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

    sem_work_init();
    shared_mem_init()
    
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

    shared_mem_release();
    
    return 0;
}

/*


 */