#include <unistd.h>
#include <fcntl.h>

int fd_set_nonblock(int fd)
{
    int ret;
    int flags = fcntl(fd, F_GETFL, 0);
    ret = fcntl(fd, F_SETFL, flags|O_NONBLOCK);

    return ret;
}
