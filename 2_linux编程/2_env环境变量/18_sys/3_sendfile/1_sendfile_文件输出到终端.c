#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>

int main(int argc, char const* argv[])
{
    int fd_in;
    fd_in = open(argv[1], O_RDONLY);
    if (fd_in < 0) {
        perror("open file failed");
        return -1;
    }
    int fd_out = STDOUT_FILENO;
    int ret;
    ret = sendfile(fd_out, fd_in, NULL, 1024);

    close(fd_in);

    return 0;
}

/*
输出文件内容正常

 */