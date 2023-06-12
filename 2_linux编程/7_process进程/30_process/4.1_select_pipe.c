#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define STRING "hello world!"

void listen_thread_cmd(int fd)
{
    struct timeval timeout;
    fd_set rd_set;
    int ret;
    int max_fd=0;

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

}

int main()
{
    int pipefd[2];
    pid_t pid;
    char buf[BUFSIZ];
    if (pipe(pipefd) == -1) {
        perror("pipe()");
        exit(1);
    }
    pid = fork();
    if (pid == -1) {
        perror("fork()");
        exit(1);
    }
    if (pid == 0) {
        /* this is child. */
        close(pipefd[1]);
        printf("Child pid is: %d\n", getpid());
        #if 0
        if (read(pipefd[0], buf, BUFSIZ) < 0) {
            perror("write()");
            exit(1);
        }
        printf("%s\n", buf);
        #endif
        listen_thread_cmd(pipefd[0]);
    } else {
        /* this is parent */
        int n = 5;
        close(pipefd[0]);
        printf("Parent pid is: %d\n", getpid());
        snprintf(buf, BUFSIZ, "Message from parent: My pid is: %d", getpid());
        while(n--)
        {
            if (write(pipefd[1], buf, strlen(buf)) < 0) {
                perror("write()");
                exit(1);
            }
            sleep(1);
        }

        wait(NULL);
    }


    exit(0);
}