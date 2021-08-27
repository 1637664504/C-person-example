
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    #define WAN_INFO "/tmp/wan_info"
    FILE *fp;
    fp = fopen(WAN_INFO,"r");
    if(fp == NULL){
        perror("fopen failed");
    }

    char buf[512]={0};
    char link[16];
    char ip[64];
    char mask[16];
    char broad[16];
    char route[16];
    char dns[16];
    fgets(buf,512,fp);
    sscanf(buf,"link=%s ip=%s mask=%s broad=%s route=%s dns=%s",link,ip,mask,
            broad,route,dns);
    printf("%s %s %s ,%s %s %s\n",link,ip,mask,broad,route,dns);

    return 0;
}

