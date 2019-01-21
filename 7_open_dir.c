
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
    char *path="/home/liuj/123/123.log";

    fd = open(path,O_RDWR|O_CREAT,0644);
    if(fd < 0){
        perror("open() failed");
        exit(1);
    }
    printf ( "open ok\n" );
 return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

