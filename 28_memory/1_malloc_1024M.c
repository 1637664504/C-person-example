
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define kMem 1024
#define MMem 1024*1024
int main ( int argc, char *argv[] )
{
    int c;
    void *p = NULL;

    p = malloc(100*MMem);
    memset(p,'d',50*MMem);
    //memset(p,'d',100*MMem);
    while(getchar() != 'q'){
        sleep(2);
        printf("input a number");
    }
    free(p);
    return 0;
}

/*
测试命令1.
ps -aux|grep a.out
USER         PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
kali      214062  1.4  5.1 104708 103344 pts/0   S+   21:53   0:00 ./a.out


测试命令2.
cat /proc/pidxx/status
VmHWM:    103344 kB
VmRSS:    103344 kB

VSZ 虚拟内存
RSS 实际占用内存，单位k
103344/1024 = 100M

其它:
未使用申请空间, VSZ 100M, RSS 0.5M
memset 50% malloc空间， VSZ 102M, RSS 51M
使用malloc之后，VSZ 102M, RSS 100M
*/