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
        perror("open file error\n");
        return -1;
    }

    // 映射文件大小不能为空
    // 方案1: write(fd, "1", 1);
    // 方案2
    ftruncate(fd, 64);
    
    ptr = (char*)mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED)
    {
        printf("mmap failed\n");
        close(fd);
        return -1;
    }

    strcpy(ptr, "hello mmap test");
    char buf[64];
    while(1)
    {
        memset(buf, 0, sizeof(buf));
        scanf("%s", buf);
        memcpy(ptr, buf, strlen(buf)+1);
        if (strncmp(ptr, "exit", 4) == 0)
        {
            break;
        }
    }

    munmap(ptr, PAGE_SIZE);

    return 0;
}