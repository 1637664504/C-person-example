/*
单进程 sem操作，验证
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>

//semop semget
#include <sys/sem.h>

union semun {
    int val;			/* value for SETVAL */
    struct semid_ds *buf;		/* buffer for IPC_STAT & IPC_SET */
    unsigned short *array;		/* array for GETALL & SETALL */
    struct seminfo *__buf;		/* buffer for IPC_INFO */
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
int sem_unlock(int id)
{
    struct sembuf semb;
    semb.sem_num = 0;
    semb.sem_op = 1;
    semb.sem_flg = SEM_UNDO;
    if(semop(sem_id,&semb,1) == -1){
        fprintf(stderr,"sem unlock error\n");
        return 0;
    }
    return 1;
}

int main(int argc,char *argv[])
{
    int ret;
    int count = 5;
    if((sem_id = semget(0x1234,1,0666|IPC_CREAT)) == -1)
    {
        perror("semget error");
        exit(-1);
    }
    sem_init_val(sem_id,1);
    while(count--){
        sem_lock(sem_id);
        printf("+++++ %d : pid= %u\n",count,getpid());
        sleep(1);
        sem_unlock(sem_id);        
    }


    return 0;
}

/* result:
+++++ 4 : pid= 92668
+++++ 4 : pid= 92669
+++++ 3 : pid= 92669
+++++ 3 : pid= 92668
+++++ 2 : pid= 92668
+++++ 2 : pid= 92669
+++++ 1 : pid= 92668
+++++ 1 : pid= 92669
+++++ 0 : pid= 92669
+++++ 0 : pid= 92668

*/
