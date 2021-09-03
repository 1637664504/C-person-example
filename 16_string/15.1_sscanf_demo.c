#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char buf[128] = "AT response:+GTETHTMAC:1,D2:22:33:44:55:61";
    char mac[18] = {0};
    int ret;

    ret = sscanf(buf,"%*[^,],%17s",mac);
    printf("ret=%d, mac=%s\n",ret ,mac);
    return 0;
}