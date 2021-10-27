#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main ( int argc, char *argv[] )
{
    char cmd[64]={0};
    int status = 0;
    int exit_code = 0;
    pid_t pid, pid_ret;
    sprintf(cmd,"ls -l");

    pid = fork();
    if(pid < 0){
        printf("fork failed\n");
        exit(1);
    }else if(pid ==0){
        printf("child 111111111 pid=%u\n",getpid());
        exit(-1);
    }

    pid_ret = waitpid(pid,&status,0);

    if(WIFEXITED(status)){
        exit_code = WEXITSTATUS(status);
        printf("pid_ret=%d, ret=%d, exit_code=%d\n",pid_ret, status, exit_code);
        printf("child exit with %d\n", WEXITSTATUS(status));
    }else if(WIFSIGNALED(status)){
        status = WTERMSIG(status);
        printf("kill child sig =%d\n",status);
    }
    printf("22222222222\n");
	return 0;
}

