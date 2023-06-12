#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define sysErr_exit(format,...) do{ \
        printf("[%s:%d]sysError(errno=%d,%s) "format,__func__, __LINE__,errno,strerror(errno), ##__VA_ARGS__); exit(errno); \
    }while(0)

int main(int argc, char *argv[])
{
    char file[]="1234.txt";
    FILE *fp = fopen(file,"r");
    if(fp == NULL)
        sysErr_exit("open file %s failed",file);

    return 0;
}