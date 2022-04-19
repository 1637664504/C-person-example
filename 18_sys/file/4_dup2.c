#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

/**dup2(oldfd,newfd)
 * if newfd is open, close newfd.
 * copy oldfd inode to newfd
**/
int main ( int argc, char *argv[] )
{
    int newfd = 7;
    int ret;
    
    ret = dup2(1,newfd);
    if(ret == -1)
    {
        perror("dup2 failed");
    }
    char buf[16]="test dup2\n";
    write(newfd,buf,sizeof(buf));
    close(newfd);

    return 0;
}
