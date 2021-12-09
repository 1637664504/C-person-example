//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
//#include <sys/types.h>
//#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>


int get_link_addr(const char *ifc_name, struct in_addr *addr)
{
    int sock = 0;
    struct ifreq ifr = {0};
    struct sockaddr_in *ifc_addr = NULL;

    if (ifc_name == NULL || addr == NULL)
    {
        return -1;
    }

    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        return -2;
    }

    strcpy(ifr.ifr_name, ifc_name);
    if (ioctl(sock, SIOCGIFADDR, &ifr) <  0)
    {
        close(sock);
        return -3;
    }
    ifc_addr = (struct sockaddr_in*)&(ifr.ifr_addr);
    memcpy(addr, &(ifc_addr->sin_addr),sizeof(struct in_addr));

    return 0;
}

int get_link_ip(char *ifcname, char *ip, unsigned int len)
{
    struct in_addr addr;
    int ret = -1;

    if(get_link_addr(ifcname,&addr))
        return -1;

    if(inet_ntop(AF_INET,(void *)&addr,ip,len))
        ret = 0;

    return ret;
}
