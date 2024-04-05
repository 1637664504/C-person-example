#include <stdio.h>
#include <string.h>

unsigned long long get_file_size_fstream(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        perror("fopen");
        return -1; // 打开文件失败
    }

    fseek(file, 0L, SEEK_END);             // 移动到文件末尾
    unsigned long long size = ftell(file); // 获取当前位置，即文件大小

    fclose(file);

    return size;
}

int main(int argc, char *argv[])
{
    char file_name[128] = "test.txt";
    if(argc == 2)
    {
        strncpy(file_name, argv[1], sizeof(file_name));
    }
    unsigned long long filesize;

    filesize = get_file_size_fstream(file_name);
    if (filesize != -1)
    {
        printf("File size: %llu bytes\n", filesize);
    }
    else
    {
        printf("Failed to get file size.\n");
    }
    return 0;
}
