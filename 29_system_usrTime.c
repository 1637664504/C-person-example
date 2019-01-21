#include	<stdlib.h>
#include    <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main ( int argc, char *argv[] )
{
    char cmd[64]="ls -al;sleep 4;ls ~";
    pid_t pid;

    pid = fork();
    if(pid==0){
    printf("liuj child start\n");
        //system(cmd);    
        execl("/bin/ls","ls","-al","> 123.log",NULL);
        printf("liuj child end\n");    
    }else if(pid < 0){
        printf("liuj fork failed. exit\n");
        exit(1);
    }

    int status;
    wait(&status);
    printf("patent over\n");
 return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

