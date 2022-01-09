#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int main(int argc, char** argv)
{
    FILE *fp = NULL;
    char cmd[]="./a.out eth3";
    fp = popen(cmd,"r");
    if(fp == NULL){
        perror("popen fail");
        exit(-1);
    }

    char buf[1024] = "";
    while(fgets(buf,sizeof(buf)-1,fp))
    {
    }
    printf("\n%s",buf);

    return 0;
}