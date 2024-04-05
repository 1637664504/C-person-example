#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    uint8_t buffer[1024];
    FILE* file_in, * file_out;
    char file_src[32] = "test.img";
    char file_dst[32] = "test_copy.img";

    file_in = fopen(file_src, "rb");
    file_out = fopen(file_dst, "wb");
    size_t len = 1;
    // 读取源文件并写入目标文件
    while (len > 0)
    {
        len = fread(buffer, 1, sizeof(buffer), file_in);
        fwrite(buffer, 1, len, file_out);
    }

    fclose(file_in);
    fclose(file_out);

    return 0;
}