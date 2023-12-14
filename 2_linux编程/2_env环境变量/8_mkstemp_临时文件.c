#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include<stdio.h>
#include<stdlib.h>
int main(void)
{
    int fd;
    char temp_file[48] = "tmp_XXXXXX";
    if ((fd = mkstemp(temp_file)) == -1)
    {
        printf("Creat temp file faile./n");
        exit(1);
    }
    close(fd);


    // 删除文件
    unlink(temp_file);

    return 0;
}