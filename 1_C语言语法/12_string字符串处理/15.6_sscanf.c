#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
注意connType的长度。
*/
void test2(void)
{
    char mac[18] = {0};
    char ip[16] = {0};
    char hostname[64] = {0};
    int uptime;
    //char connType[8] = {0};
    char connType[16] = {0};

    int ret;
    char buf[128]="02:4f:cb:35:9a:a8 192.168.1.201 iQOO-Neo5 162 guest_5G";
    ret = sscanf(buf,"%17s %15s %s %d %s",mac,ip,hostname,&uptime,connType);
    //ret = sscanf(buf,"%[^ ] %[0-9.^ ] %[^ ] %d %[^ ]",mac,ip,hostname,&uptime,connType);
    printf("ret=%d: %s, %s, %s, %d, %s\n",ret,mac,ip,hostname,uptime,connType);
}

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
    printf("12 dns=%s,%s\n",dns1,dns2);

    test2();
    return 0;
}