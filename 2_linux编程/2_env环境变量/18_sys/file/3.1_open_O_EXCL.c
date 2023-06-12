#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main ( int argc, char *argv[] )
{
    char file[16]="test";
    int fd;
    //fd = open(file,O_CREAT|O_EXCL,0644);
    fd = open(file,O_EXCL,0644);
    if(fd < 0){
        perror("open file failed");
    }

    return 0;
}
