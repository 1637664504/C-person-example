#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
 writev(fd,iov,iov_num);
 多次写， 变更为一次写. 减少系统开销
*/
int main ( int argc, char *argv[] )
{
    int fd;

    struct iovec iov[2];
    char buf1[16]="123456789";
    char buf2[16]="abcdefgh";

    char file[16]="test";
    fd = open(file,O_WRONLY);
    if(fd < 0)
    {
        perror("open file failed");
        exit(-1);
    }

    int i=0;
    iov[i].iov_base = buf1;
    iov[i].iov_len = strlen(buf1)+1;

    i++;
    iov[i].iov_base = buf2;
    iov[i].iov_len = strlen(buf2)+1;

    int len = writev(fd,iov,2);
    if(len == -1)
    {
        perror("writev failed");
    }
    printf("write len=%d\n",len);

    close(fd);

    return 0;
}
