#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char buf[128] = "2408:8557:3031:4031:16af:f5a7:a192:1cd4/64";
    char ip[16] = {0};
    char mac[18] = {0};

    sscanf(buf,"%s",ip);
    printf("ip=%s\n",ip);

    return 0;
}