#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

size_t fseek_read(char* file, size_t offset, FILE* dst_fp)
{
    FILE* fp = fopen(file, "rb");
    if (fp == NULL)
        return 0;
    fseek(fp, offset, SEEK_SET);
    uint8_t buf[1024];
    size_t len = fread(buf, 1, sizeof(buf), fp);
    fwrite(buf, 1, len, dst_fp);

    return len;
}

int main(int argc, char* argv[])
{
    size_t offset = 0;
    size_t len = 1;
    char file_src[32] = "test.img";
    char file_dst[32] = "dst.img";
    FILE* fp_dst = fopen(file_dst, "wb");
    while (len > 0)
    {
        len = fseek_read(file_src, offset, fp_dst);
        offset += len;
    }
    fclose(fp_dst);

    // 验证文件是否相同
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "du -b %s %s", file_src, file_dst);
    system(cmd);
    snprintf(cmd, sizeof(cmd), "md5sum %s %s", file_src, file_dst);
    system(cmd);

    return 0;
}