#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>


int main ( int argc, char *argv[] )
{
    int ret;
    ret = syscall(SYS_getpid);
    printf("%d\n",ret);

    pid_t pid;
    pid = getpid();
    printf("pid=%d\n",pid);
	return 0;
}	




