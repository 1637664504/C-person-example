
#include	<stdlib.h>
#include    <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX 32

char *route;
int main ( int argc, char *argv[] )
{
    char buf[256];
    snprintf(buf, 255, "/sbin/ip route get 192.168.1.2" );
    FILE *p = popen(buf, "r");
    fgets(buf, 255, p);
    route = strdup(buf);
    printf("--buf=%s \n++route=%s\n",buf,route);
    pclose(p);
}
