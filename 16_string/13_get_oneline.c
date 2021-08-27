#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char buf[64] = "00:50:56:2f:43:d9\n14:6b:9c:bd:46:8d\n";
    char str[32] = {0};
    char *p;
    
    p = buf;
    while(sscanf(p,"%[^\n]", str) > 0)
    {
        printf("str=%s\n",str);
        p += strlen(str)+1;
    }

#if 1
    char *p_buf;
    p_buf = buf;
    while(p=strchr(p_buf,'\n')){
        *p = '\0';
        printf("mac=%s\n",p_buf);
        p_buf=p+1;
    }
#endif
    return 0;
}