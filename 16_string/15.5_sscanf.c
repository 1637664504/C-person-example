#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char buf[128] = "240e:47c:30a8:7fee:16af:f622:90cf:8477/64";
    char ip[64] = {0};
    int prefix_len =0;

    sscanf(buf,"%[^/]/%d",ip,&prefix_len);
    printf("ip=%s, prefix_len=%d\n",ip,prefix_len);

    return 0;
}