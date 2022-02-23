#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char buf[256]="link=eth1 ip=192.168.40.100 mask=255.255.255.0 broad=192.168.40.254 route=192.168.40.1 dns=223.5.5.5 8.8.8.8";
    char ifname[16];
    char ip[16];
    char mask[16];
    char getways[16];
    char broad[16];
    char dns1[16];
    char dns2[16];
    sscanf(buf,"link=%[^ ] ip=%[^ ] mask=%[^ ] broad=%[^ ] route=%[^ ] dns=%[^ ] %[^ ]",
        ifname,ip,mask,broad,getways,dns1,dns2);
    printf("11 %s,%s,%s,%s,%s\n",ifname,ip,mask,broad,getways);

    //char buf2[64]="dns=223.5.5.5 8.8.8.8";
    //sscanf(buf2,"dns=%[^ ] %[^ ]",dns1,dns2);
    printf("12 dns=%s,%s",dns1,dns2);

    return 0;
}