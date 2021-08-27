#include<stdio.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define MAX_STU 16
#define KEY 7788

struct demo{
    int age;
    char name[64];
} stu[MAX_STU];

int main()
{
    int shm_id;
    void* shm_p = NULL;
    shm_id = shmget(KEY,sizeof(stu),0644|IPC_CREAT);
    if(shm_id == -1){
        printf("shmget failed: %s",strerror(errno));
        exit(-1);
    }
    shm_p = shmat(shm_id,NULL,0);
    struct demo *p=(struct demo*)shm_p;
    p->age=11;
    (p+1)->age=12;
    printf("%d %d\n",p->age,(p+1)->age);
    if(shmdt(shm_p) == -1){
        printf("shmat failed %s\n",strerror(errno));
        exit(-1);
    }
    
    printf("11111\n");
    return 0;
}