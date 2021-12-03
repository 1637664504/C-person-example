/*
字符串提取验证
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main ( int argc, char *argv[] )
{
    char buf[128]="RX bytes:1184973 (1.1 MiB) TX bytes:422954 (413.0 KiB)";
    char *p=buf;
    unsigned long rx = 0, tx = 0;

    if((p=strchr(buf,':')))
        rx= atoi(++p);
    //if((p=strrchr(buf,':')))
    if((p=strchr(p,':')))
        tx = atoi(++p);

    printf("rx=%lu, tx=%ld\n",rx,tx);

    return 0;
}