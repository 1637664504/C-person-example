#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main ( int argc, char *argv[] )
{
    FILE *fp = fopen("/proc/net/dev","r");
    if(!fp)
    {
        perror("system not support.");
        exit(-1);
    }

    char oneline[256]={0};
    int i=0;
    while(fgets(oneline,sizeof(oneline)-1,fp)){
        printf("%d: %s",i++,oneline);
        memset(oneline,'\0',sizeof(oneline));
    }

    return 0;
}