#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char buf[32] = "ff";
    int num;

    printf("num=%ld\n",strtol(buf, NULL, 16));

    return 0;
}