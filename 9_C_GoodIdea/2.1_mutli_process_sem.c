/*
多进程 sem操作，验证
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>

//semop semget
#include <sys/sem.h>

union semun {
    int val;			/* value for SETVAL */
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
    void *__pad;
};
static int sem_id;

int sem_init_val(int id,int val)
{
    union semun ctl;
    ctl.val = val;
    if(semctl(id, 0, SETVAL, ctl) == -1)
        return 0;
    return 1;
}

void sem_delete(int id)
{
    union semun ctl;
    if(semctl(id, 0, IPC_RMID, ctl) == -1)
        fprintf(stderr,"delete sem error\n");
}

int sem_lock(int id)
{
    struct sembuf semb;
    semb.sem_num = 0;
    semb.sem_op = -1;
    semb.sem_flg = SEM_UNDO;
    if(semop(sem_id,&semb,1) == -1){
        fprintf(stderr,"sem lock error\n");
        return 0;
    }
    return 1;
}
#define MSECS_IN_SEC  1000
int sem_trylock_timout(int id,int msec,char *func)
{
    struct timespec ts;
    int ret;
    struct sembuf semb;
    
    semb.sem_num = 0;
    semb.sem_op = -1;
    semb.sem_flg = SEM_UNDO;

    ts.tv_sec = msec/MSECS_IN_SEC;
    ts.tv_nsec = (msec%MSECS_IN_SEC)*MSECS_IN_SEC;

    ret = semtimedop(id,&semb,1,&ts);
    if(ret == 0){
        printf("get sem lock right\n");
        update_info(func);
    }else{
        printf("get sem_lock fail\n");
    }
    return ret;
    
}
int sem_unlock(int id)
{
    struct sembuf semb;
    semb.sem_num = 0;
    semb.sem_op = 1;
    semb.sem_flg = SEM_UNDO;
    if(semop(sem_id,&semb,1) == -1){
        fprintf(stderr,"sem unlock error\n");
        return -1;
    }
    return 0;
}

int main(int argc,char *argv[])
{
    int ret;
    int count = 5;
    int pid;
    if((sem_id = semget(0x1234,1,0666|IPC_CREAT)) == -1)
    {
        perror("semget error");
        exit(-1);
    }
    sem_init_val(sem_id,1);

    pid = fork();
    if(pid == 0){
        printf("I am coustmer\n");
        while(count --){
            sem_lock(sem_id);
            printf("pid=%u ++++++++++ %d\n",getpid(),count);
            sleep(5);
            sem_unlock(sem_id);
        }
    }else{
        printf("I am producer\n");
        while(count --){
            if(sem_trylock_timout(sem_id,1)){
                printf("coutinue\n");
                continue;
            }
            printf("pid=%u ----- %d\n",getpid(),count);
            sleep(1);
            sem_unlock(sem_id);
        }
    }
    //sem_delete(sem_id);

    return 0;
}

/* result:
I am producer
I am coustmer
get sem lock right
pid=92877 ----- 4
pid=92878 ++++++++++ 4
get sem_lock fail
coutinue
get sem_lock fail
coutinue
get sem_lock fail
coutinue
get sem_lock fail
coutinue
liuj@22:~/1_Dada/5_C_example/9_C_GoodIdea$ pid=92878 ++++++++++ 3
pid=92878 ++++++++++ 2
pid=92878 ++++++++++ 1
pid=92878 ++++++++++ 0


*/

