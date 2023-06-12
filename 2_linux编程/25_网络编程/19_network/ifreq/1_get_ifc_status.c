#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
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
    close(sock);

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


int get_link_attribute(const char *ifname, int request, char *buf, unsigned int len)
{
    int sock = 0;
    int ret = 0;
    struct ifreq ifr = {0};
    struct in_addr addr = {0};
    struct sockaddr_in *ifc_addr = NULL;

    if (ifname == NULL || buf == NULL)
    {
        return -1;
    }

    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        return -2;
    }

    strcpy(ifr.ifr_name, ifname);
    if (ioctl(sock, request, &ifr) <  0)
    {
        close(sock);
        return -3;
    }
    switch(request)
    {
        case SIOCGIFNETMASK:
            ifc_addr = (struct sockaddr_in*)&(ifr.ifr_netmask);
            memcpy(&addr, &(ifc_addr->sin_addr),sizeof(struct in_addr));
            if(inet_ntop(AF_INET,(void *)&addr,buf,len));
                ret = 0;
            break;
        case SIOCGIFDSTADDR:
            ifc_addr = (struct sockaddr_in*)&(ifr.ifr_dstaddr);
            memcpy(&addr, &(ifc_addr->sin_addr),sizeof(struct in_addr));
            if(inet_ntop(AF_INET,(void *)&addr,buf,len));
                ret = 0;
            break;
    }
    close(sock);

    return ret;
}


int get_link_mac(char *ifcname, unsigned char *mac, unsigned int len)
{
    struct ifreq ifreq = {0};
    int sock;

    if(!ifcname || !mac || len < IFHWADDRLEN)
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
    memcpy(mac,ifreq.ifr_hwaddr.sa_data,IFHWADDRLEN);
    close(sock);

    return 0;
}

int get_link_flags(char *ifname, short int *flags)
{
    struct ifreq ifr;
    int sock;
    int ret = 0;

    if(!ifname || !flags)
        return -1;

    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        return -1;
    }

    strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name)-1);
    ret = ioctl(sock, SIOCGIFFLAGS, &ifr);
    if(ret)
        return -1;

    close(sock);
    *flags = ifr.ifr_flags;

    return 0;
}

int main()
{
    char ifname[16]="ppp1";
    char mask[16]="";
    int ret = -1;
    ret = get_link_attribute(ifname,SIOCGIFNETMASK,mask,sizeof(mask)-1);
    printf("mask=%s,ret=%d\n",mask,ret);

    //ppp1
    char ip[16]="";
    ret = get_link_attribute("ppp1",SIOCGIFDSTADDR,ip,sizeof(ip)-1);
    printf("d_ip=%s,ret=%d\n",ip,ret);

    short int flag = 0;
    ret = get_link_flags(ifname,&flag);
    printf("flag=%d,ret=%d\n",flag,ret);

    return 0;
}