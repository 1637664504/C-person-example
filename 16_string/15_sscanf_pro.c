#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char buf[128] = "? (192.168.1.2) at 14:6b:9c:bd:46:8d [ether]  on br-lan";
    char ip[16] = {0};
    char mac[18] = {0};
    sscanf(buf,"%*s (%15[. 0-9]) at %17[: 0-9 a-z]",ip,mac);
    printf("ip=%s,mac=%s\n",ip,mac);
    return 0;
}