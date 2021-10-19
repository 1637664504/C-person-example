#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char buf[128] = "192.168.1.133 14:6b:9c:bd:46:8d";
    char ip[16] = {0};
    char mac[18] = {0};

    sscanf(buf,"%15s[^ ]",ip);
    printf("ip=%s\n",ip);

    return 0;
}