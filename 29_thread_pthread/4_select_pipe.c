#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#define STRING "hello world!"
int pipefd[2];

void* listen_thread_cmd(void *arg)
{
    struct timeval timeout;
    fd_set rd_set;
    int ret;
    int max_fd=0;
    int fd = pipefd[0];

    while(1)
    {
        FD_ZERO(&rd_set);
        FD_SET(fd, &rd_set);
        memset(&timeout,0,sizeof(timeout));
        timeout.tv_sec = 4;
        if(max_fd <= fd)
            max_fd = fd+1;
        
        ret = select(fd+1,&rd_set,NULL,NULL,&timeout);
        if(ret < 0)
        {
            perror("select fail\n");
            exit(-1);
        }
        else if(ret == 0)
        {
            printf("select timeout\n");
            continue;
        }
        
        if(FD_ISSET(fd,&rd_set))
        {
            char buf[64]="";
            int len = read(fd,buf,sizeof(buf)-1);
            printf("buf=%s\n",buf);
        }
    }

    return NULL;
}

int main()
{
    
    pid_t pid;
    char buf[BUFSIZ];
    pthread_t tid;
    void *ret;
    int n = 20;

    if (pipe(pipefd) == -1) {
        perror("pipe()");
        exit(1);
    }
    pthread_create(&tid, NULL, listen_thread_cmd, NULL);
    pthread_detach(tid);
     
        while(n--)
        {
            printf("main thread write msg\n");
            snprintf(buf, BUFSIZ, "pid=%d msg n=%d \n", getpid(),n);
            if (write(pipefd[1], buf, strlen(buf)) < 0) {
                perror("write()");
                exit(1);
            }
            sleep(2);
        }

    return 0;
}