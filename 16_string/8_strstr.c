/*
判断字符串 是否 \n \t 存在
*/
#include <string.h>

int main(void)
{
    char buf[256]="nameserver 223.5.5.5\n\
        nameserver 8.8.8.8\n\
        nameserver 2400:3200:baba::1";
    
    int a=0,b=0,c=0,d=0;
    if(strstr(buf,"223.5.5.5"))
        a=1;
    if(strstr(buf,"8.8.8.4"))
        b=1;
    if(strstr(buf,"2400:3200:baba::1"))
        c=1;
    //if dst is empty "", return true
    if(strstr(buf,""))
        d=1;
    return 0;
}