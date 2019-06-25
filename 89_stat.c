#include	<stdlib.h>
#include    <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main ( int argc, char *argv[] )
{
    int ret,ret2;
    struct stat buf;
    ret = stat("89_stat.c",&buf);
    ret2 = stat("99_123.c",&buf);
    printf("ret=%d,ret2=%d\n",ret,ret2);
    return EXIT_SUCCESS;
}
