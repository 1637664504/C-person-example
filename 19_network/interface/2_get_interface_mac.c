#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>

#define MAC_LEN 6
int get_ifcname_mac(char *ifcname, char *mac, unsigned int len)
{
    struct ifreq ifreq = {0};
    int sock;
    int ret = -1;

    if(!ifcname || !mac || len < MAC_LEN)
        return -1;

    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
            return -2;
    }

    strncpy(ifreq.ifr_name,ifcname,sizeof(ifreq.ifr_name));
    if(ioctl(sock,SIOCGIFHWADDR,&ifreq)<0)
    {
            return -3;
    }
    memcpy(mac,ifreq.ifr_hwaddr.sa_data,MAC_LEN);

    return ret;
}
void show_hex(unsigned char* src, unsigned int len)
{
    for(int i=0; i<len; i++){
        printf("%02x ",*(unsigned char*)(src+i));
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    char mac[MAC_LEN]="";
    get_ifcname_mac("eth1",mac,sizeof(mac));
    show_hex(mac,sizeof(mac));
    printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                        (unsigned char)mac[0],
                        (unsigned char)mac[1],
                        (unsigned char)mac[2],
                        (unsigned char)mac[3],
                        (unsigned char)mac[4],
                        (unsigned char)mac[5]);

    return 0;
}