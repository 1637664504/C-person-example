#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char buf[128] = "2408:8456:3a10:ca90:b02d:fbff:fe5c:6232/64";
    char ip[64] = {0};
    char *p = NULL;
    int prefix_len =0;

    //sscanf(buf,"%39[^/]/%d",ip,&prefix_len);
        p = strchr(buf,'/');
        strncpy(ip,buf,p-buf);
        prefix_len = atoi(++p);
    printf("ip=%s, prefix_len=%d\n",ip,prefix_len);

    return 0;
}