/*
多进程 实现博通的 cms_trylock_timeout(time);
process A: trylock 中
process B: trylock_timeout(time),
        提示 process: pid=xx,func=%s,timeout=%ul

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

//semop semget
#include <sys/shm.h>
#include <sys/sem.h>

struct thread{
    int flag;
    unsigned int pid;
    char func_name[64];
    time_t time;
};
union semun {
    int val;			/* value for SETVAL */
    struct semid_ds *buf;		/* buffer for IPC_STAT & IPC_SET */
    unsigned short *array;		/* array for GETALL & SETALL */
    struct seminfo *__buf;		/* buffer for IPC_INFO */
    void *__pad;
};
static int sem_id;
struct thread *p;

void update_info(const char *func)
{
    p->flag =1;
    p->pid = getpid();
    strcpy(p->func_name,func);
    p->time = time(NULL);
}
void display_info()
{
    time_t now;
    now = time(NULL);
    printf("Occuy by pid=%u,func=%s,timeout=%ld\n",p->pid,p->func_name,now-p->time);
}
void clean_info()
{
    memset(p,0,sizeof(struct thread));
}

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
#define MSECS_IN_SEC  1000

int sem_lock(int id,const char *func)
{
    struct sembuf semb;
    semb.sem_num = 0;
    semb.sem_op = -1;
    semb.sem_flg = SEM_UNDO;
    if(semop(sem_id,&semb,1) == -1){
        fprintf(stderr,"sem lock error\n");
        return 0;
    }
    update_info(func);
    return 1;
}


int sem_trylock_timout(int id,int msec,const char *func)
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
        //printf("get sem lock right\n");
        update_info(func);
    }else{
        //printf("get sem_lock fail\n");
        display_info();
    }
    return ret;
    
}

void sem_unlock(int id)
{
    struct sembuf semb;
    semb.sem_num = 0;
    semb.sem_op = 1;
    semb.sem_flg = SEM_UNDO;
    if(semop(sem_id,&semb,1) == -1){
        fprintf(stderr,"sem unlock error\n");
    }else{
        clean_info();
    }
}

void processA(void)
{
    int count = 5;
    while(count --){
        if(sem_trylock_timout(sem_id,2*MSECS_IN_SEC,__func__)){
            continue;
        }
        printf("++++++++++ %d\n",count);
        sleep(10);
        sem_unlock(sem_id);
    }
}

void processB(void)
{
    int count=5;
    while(count --){
        if(sem_trylock_timout(sem_id,1*MSECS_IN_SEC,__func__)){
            continue;
        }
        printf("----- %d\n",count);
        sleep(1);
        sem_unlock(sem_id);
    }
}

int main(int argc,char *argv[])
{
    int ret;
    int count = 5;
    int pid;
    void *mem;
    int shm_id;

    //1. sem init
    if((sem_id = semget(0x1234,1,0666|IPC_CREAT)) == -1)
    {
        perror("semget error");
        exit(-1);
    }
    sem_init_val(sem_id,1);

    //2.share mem init
    shm_id = shmget(0x1234,sizeof(struct thread),0666|IPC_CREAT);
    if(shm_id == -1){
        fprintf(stderr,"shmget error\n");
        exit(-1);
    }
    mem = shmat(shm_id,NULL,0);
    if(mem == -1){
        perror("shmat fail");
        exit(-1);
    }
    p = (struct thread *)mem;
    memset(p,0,sizeof(struct thread));

    pid = fork();
    if(pid == 0){
        printf("I am coustmer\n");
        processB();
    }else{
        printf("I am producer\n");
        processA();
    }
    if(shmdt(mem) == -1){
        perror("shmdt fail");
        exit(-1);
    }

    return 0;
}

/* result:
I am producer
I am coustmer
++++++++++ 4
Occuy by pid=93084,func=processA,timeout=1
Occuy by pid=93084,func=processA,timeout=2
Occuy by pid=93084,func=processA,timeout=3
Occuy by pid=93084,func=processA,timeout=4
Occuy by pid=93084,func=processA,timeout=5
++++++++++ 3
++++++++++ 2
++++++++++ 1
++++++++++ 0

*/

