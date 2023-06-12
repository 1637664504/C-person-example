#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

/**newfd = dup(oldfd)
 * copy oldfd inode to newfd. return a small number
**/
int main ( int argc, char *argv[] )
{
    int newfd;
    int ret;
    
    newfd = dup(1);
    if(newfd == -1)
    {
        perror("dup failed");
    }
    char buf[16]="test dup2\n";
    write(newfd,buf,sizeof(buf));
    close(newfd);

    return 0;
}
