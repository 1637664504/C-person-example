#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
  
  int main ( int argc, char *argv[] )
  {
    int pid,sid;
    pid = getpid();
    sid = getsid(pid);
    printf("111 pid=%d,sid=%d\n",pid,sid);
    
    printf("liuj--  \n");

    sid = setsid();
    if(sid < 0){
        printf("liuj--:set setsid error \n");
        exit(1);
    }
    pid = getpid();
    sid = getsid(pid);
    printf("222 pid=%d,sid=%d\n",pid,sid);
    
    return 0;
  }   




