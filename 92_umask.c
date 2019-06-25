#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

 
int main(int argc, char *argv[])
{
    int ret;
    ret=umask(0777);
    printf("11 ret=%d\n",ret);
    ret=umask(ret|022);
    printf("22 ret=%d\n",ret);
    return 0;
}
