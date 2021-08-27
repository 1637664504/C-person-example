#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char buf[32] = "ff";
    char *p_end;
    int num;

    printf("num=%d\n",strtol(buf, &p_end, 16));

    return 0;
}