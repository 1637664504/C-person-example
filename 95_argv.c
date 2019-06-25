
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
void printf_argv(char **argv)
{
    printf("-----%s %s\n",argv[1],argv[2]);
}


int main(int argc,char **argv)
{
    printf("%d\n",argc);
    printf_argv(argv);
    return 0;
}

