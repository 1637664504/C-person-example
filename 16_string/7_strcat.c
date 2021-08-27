#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char buf[32]={0};
    char a[16]="111";
    char b[16]="aaa";
    char *p;

    p=strcat(buf,a);
    p=strcat(buf,b);
    printf("buf=%s\n",buf);
    return 0;
}