/*
多进程 共享内存测试
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

//semop semget
#include <sys/shm.h>
struct golab_mutex{
    int flag;
    unsigned int pid;
    char func_name[64];
    time_t time;
};
int main(int argc,char *argv[])
{
    int ret;
    int count = 5;
    int pid;
    void *mem;
    struct thread *p;
    int shm_id;

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
        p->pid = getpid();
        strcpy(p->func_name,"aaa");
        p->time = time(NULL);

    }else{
        printf("I am producer\n");
        sleep(1);
        printf("pid=%u,func=%s,time=%u\n",p->pid,p->func_name,p->time);
    }
    if(shmdt(mem) == -1){
        perror("shmdt fail");
        exit(-1)
    }

    return 0;
}

/* result:

*/


