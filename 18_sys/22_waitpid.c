#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main ( int argc, char *argv[] )
{
    char cmd[64]={0};
    int ret,tmp;
    pid_t pid, pid_ret;
    sprintf(cmd,"ls -l");

    pid = fork();
    if(pid < 0){
        printf("fork failed\n");
        exit(1);
    }else if(pid ==0){
        printf("child 111111111\n");
    }

    pid_ret = waitpid(pid,&ret,0);

    if(WIFEXITED(ret)){
        tmp = WEXITSTATUS(ret);
        printf("pid_ret=%d, ret=%d, tmp=%d\n",pid_ret, ret,tmp);
    }else if(WIFSIGNALED(ret)){
        ret = WTERMSIG(ret);
        printf("kill child sig =%d\n",ret);
    }
    printf("22222222222\n");
	return 0;
}

