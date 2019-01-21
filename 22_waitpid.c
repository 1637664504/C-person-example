#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
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
        //return 0; //abnormal
        //return 1;     //normal, set ret 1

        
        //exit(0);        //normal
        //exit(1);        //normal,set ret 1

        //abort();      //ab
        //kill(getpid(),SIGINT);        //ab
        //ret=ret/0;

        //execl("/bin/ls","ls","-l");
        //execl("/bin/ping","ping","-c 2 ","192.168.1.1",NULL);
        //execl("/bin/ls","-l","123.c",NULL);
        
    }

    //pid_ret = waitpid(pid,&ret,0);
    //wait(&ret);
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

