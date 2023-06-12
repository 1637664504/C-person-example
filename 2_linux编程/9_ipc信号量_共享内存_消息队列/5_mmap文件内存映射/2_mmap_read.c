#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include "common.h"

int main(int argc, char* argv[])
{
    int fd = 0;
    char *ptr = NULL;
 
    if ((fd = open(MMAP_FILE, O_RDWR)) < 0)
    {
        printf("open file error\n");
        return -1;
    }
 
    ptr = (char *)mmap(NULL, PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED)
    {
        printf("mmap failed\n");
        close(fd);
        return -1;
    }

    char buf[64];
    char cmd;
    
    while ((cmd = getchar()))
    {
        if (cmd == 'q')
            break;
        else if (cmd == 'n')
        {
            memset(buf, 0, sizeof(buf));
            memcpy(buf, ptr, strlen(ptr));
            printf("buf=%s\n", buf);
        }
    }
        munmap(ptr, PAGE_SIZE);

    return 0;
}