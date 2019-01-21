
#include	<stdlib.h>
#include    <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main ( int argc, char *argv[] )
{
    int fd;
    char *path="/home/liuj/123";

    fd = mkdir(path,0771);
    if(fd < 0){
        perror("open() failed");
        exit(1);
    }
    printf ( "mkdir ok\n" );
 return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

