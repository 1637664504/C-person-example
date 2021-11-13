#include <stdio.h>
#include <string.h>
#include <errno.h>


int get_net_device_stats(const char *ifname)
{
    FILE *fp;
    char buf[128];
    fp = popen("ifconfig ppp0","r");
    if(!fp)
        return -1;
    
    while(fgets(buf,sizeof(buf)-1,fp)){
        printf("-- %s",buf);
    }
}

int main(int argc, char *argv[])
{
    get_net_device_stats("ppp0");
    return 0;
}