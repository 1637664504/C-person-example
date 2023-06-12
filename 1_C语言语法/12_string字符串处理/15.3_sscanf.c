#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char buf[256]="link=eth1 ip=192.168.5.228 mask=255.255.255.0 broad=192.168.5.255 route=192.168.5.1 dns=8.8.8.8 8.8.4.4\n";
    //char buf[256]="link=eth1 ip=192.168.5.228 mask=255.255.255.0 broad=192.168.5.255 route=192.168.5.1 dns=8.8.8.8";
    char *p;
    char link[8],ip[16],mask[16],broad[16],route[16],dns1[16],dns2[16];
 
    //sscanf(buf,"link=%s ip=%s mask=%s broad=%s route=%s dns=%s",link,ip,mask,broad,route,dns); // OK
    //sscanf(buf,"%*[^m]mask=%15[^ ] broad=%15[^ ] route=%15[^ ] dns=%15[^ ]",mask,broad,route,dns);
    if(p = strstr(buf,"route="))
        sscanf(p,"route=%[^ ]",route);
    
    if(p = strstr(buf,"dns="))
        sscanf(p,"dns=%15[^  \n] %15[^  \n]",dns1,dns2);
    //printf(":: %s,%s,%s,%s\n",mask,broad,route,dns);
    printf("::%s,%s,%s--\n",route,dns1,dns2);
    return 0;
}