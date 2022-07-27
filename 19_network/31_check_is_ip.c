/*
自己写的ipv4有效性判断
通过字符串格式解析
*/

#include <stdio.h>
#include <string.h>

int jrd_system_is_ip(const char *ip) 
{
    int part1 = 0;
    int part2 = 0;
    int part3 = 0;
    int part4 = 0;

    if (ip == NULL) 
    {
        return 0;
    }

    if (sscanf(ip, "%d.%d.%d.%d ",&part1, &part2, &part3, &part4) == 4 &&
        part1 >= 0 && part1 <= 255 && part2 >= 0 && part2 <= 255 &&
        part3 >= 0 && part3 <= 255 && part4 >= 0 && part4 <= 255)
    {
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char web[4][32]={
        "192.168.5.1",
        "355.265.12.956",
        "www.baidu.com",
        "1111111.com"
    };

    int ret;
    int i=0;
    for(; i< 4;i++)
    {
        ret = jrd_system_is_ip(web[i]);
        printf("ip=%s ret=%d\n",web[i],ret);
    }
    return 0;
}