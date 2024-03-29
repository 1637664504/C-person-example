#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if(pid == 0){               //子进程
        printf("child --- my parent is %u, pid=%u\n", getppid(),getpid());
        exit(0);              //子进程睡眠30秒
        printf("child is die\n");
     }else if(pid>0){           //父进程
        wpid = wait(&status);   //等待回收子进程
        if(wpid == -1){
            perror("wait error:");
            exit(1);
        }
        //正常退出判断
        if(WIFEXITED(status)){
            printf("child exit with %d\n", WEXITSTATUS(status));
        }

        //因为某种信号中断获取状态
        if(WIFSIGNALED(status)){
            printf("child killed by %d\n", WTERMSIG(status));
        }
     }
    printf("parent pid = %d, sonpid = %d\n", getpid(), pid);
    return 0;
}