#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
 readv(fd,iov,iov_num);
 1.多次读， 变更为一次读. 减少系统开销
 2.读取 而二进制文件常用，因为大小固定
*/
int main ( int argc, char *argv[] )
{
    int fd;
    struct iovec iov[2]="";

    char file[16]="test";
    fd = open(file,O_RDONLY);
    if(fd < 0)
    {
        perror("open file failed");
        exit(-1);
    }

    char buf1[64]="";
    char buf2[64]="";
    int nr;
    int i=0;
    iov[i].iov_base = buf1;
    iov[i].iov_len = sizeof(buf1);

    i++;
    iov[i].iov_base = buf2;
    iov[i].iov_len = sizeof(buf2);
    
    nr = readv(fd,iov,2);

    for(i=0;i<2;i++)
    {
        printf("i=%d : %s\n",i,(char *)iov[i].iov_base);
    }
    while(iov)
    close(fd);

    return 0;
}
