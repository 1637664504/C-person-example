#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc,char *argv[])
{
    char buf[64]="";
    char cmd[64]="";
    int count=0;
    int fd=open("1.txt",O_RDWR);
    if(fd < 0){
        perror("cant open file");
        exit(1);
    }
    while(count < 3){
        read(fd,buf,64);
        printf("input :quit to exit\n");
        scanf("%s",cmd);
    }
    return 0;
}
