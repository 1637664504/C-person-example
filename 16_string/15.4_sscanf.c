#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char buf[128] = "2408:8557:3031:4031:16af:f5a7:a192:1cd4/64";
    char ip[64] = {0};
    int mask=0;

    sscanf(buf,"%[^/]/%d",ip,&mask);
    printf("ip=%s,mask=%d\n",ip,mask);

    return 0;
}