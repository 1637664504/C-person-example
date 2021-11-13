#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main ( int argc, char *argv[] )
{
    char buf[64]= "11111111111111";

    sprintf(buf,"%s %s","aaa","bbb");
    printf("buf=%s\n",buf);
    return 0;
}