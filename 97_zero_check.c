#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char **argv)
{
    unsigned char mac[6]={0x0,0x0,0x1,0x2,3,4};
    char str='\0';

    if(str == mac[0]){
        printf("111111\n");
    }else{
        printf("222222\n");
    }
    return 0;
}

