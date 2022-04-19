/*
判断字符串 是否 \n \t 存在
*/
#include <string.h>

int main(void)
{
    char buf[256]="nameserver 223.5.5.5\n\
        nameserver 8.8.8.8\n\
        nameserver 2400:3200:baba::1";
    
    int len = strlen(buf);
    int overWriteFlag = 0;
    char dns[4][64]={
        "8.8.8.8",
        "223.5.5.5",
        //"8.8.8.4"
    };
    if((dns[0][0] && !strstr(buf,dns[0]))
        || (dns[1][0] && !strstr(buf,dns[1]))
        || (dns[2][0] && !strstr(buf,dns[2]))
        || (dns[3][0] && !strstr(buf,dns[3])))
    {
        overWriteFlag = 1;
    }
    return 0;
}