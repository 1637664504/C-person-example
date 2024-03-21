#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int get_file_size(const char *path, off_t *size)
{
    struct stat sb;

    if (stat(path, &sb) == -1)
    {
        perror("stat");
        return -1;
    }

    // 如果文件是一个普通文件并且成功获取了信息
    if (S_ISREG(sb.st_mode))
    {
        *size = sb.st_size;
        return 0; // 成功
    }
    else
    {
        fprintf(stderr, "Not a regular file.\n");
        return -1; // 失败（非普通文件）
    }
}

int main(int argc, char *argv[])
{
    // 使用示例
    off_t size;
    char file_name[128] = "test.txt";
    if(argc == 2)
    {
        strncpy(file_name, argv[1], sizeof(file_name));
    }

    if (get_file_size(file_name, &size) == 0)
    {
        printf("File size: %ld bytes\n", size);
    }
    else
    {
        printf("Failed to get file size.\n");
    }

    return 0;
}

/*
测试1:
# du -b 1_access.c
211     1_access.c

# ./11_state_获取文件大小.out 1_access.c
File size: 211 bytes


测试2:
# ./11_state_获取文件大小.out 3.1_open_O_EXCL.c
File size: 328 bytes

# du -b 3.1_open_O_EXCL.c
328     3.1_open_O_EXCL.c

 */