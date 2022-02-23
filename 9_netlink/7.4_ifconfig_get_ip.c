#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int get_link_ip(char *address,unsigned int len)
{
    int sock = 0;
    struct ifreq ifr;
    
    if (address == NULL || size < 16)
    {
        return -1;
    }

    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf( "create sock fail; %s\n",strerror(errno));
        return 0;
    }

    memset(&ifr,0,sizeof(ifr));
    strcpy(ifr.ifr_name, "ppp0");
    if (ioctl(sock, SIOCGIFADDR, &ifr) <  0)
    {
        printf("ioctl get addr fail: %s\n",strerror(errno));
        return 0;
    }
    strncpy(address,inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr),size);
    close(sock);

    return 0;
}

#if 1
int main()
{
        int inet_sock={0};
        char wan_ip[64]={0};
    jrd_sys_get_wan_ip(wan_ip,64);
    printf("wan=%s \n",wan_ip);
        return 0;
}
#else
int main()
{
        int inet_sock={0};
        char wan_ip[64]={0};
        struct ifreq ifr;
        struct in_addr addr;
         struct sockaddr_in *ifc_addr = NULL;
        inet_sock = socket(AF_INET, SOCK_DGRAM, 0);
 
        strcpy(ifr.ifr_name, "eth1");
        //SIOCGIFADDR标志代表获取接口地址
        if (ioctl(inet_sock, SIOCGIFADDR, &ifr) <  0)
                perror("ioctl error");
        strncpy(wan_ip,inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr),64);
        ifc_addr = (struct sockaddr_in*)&(ifr.ifr_addr);
        memcpy(&addr, &(ifc_addr->sin_addr),sizeof(struct in_addr));
        //memcpy(&addr,&((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr , sizeof(struct in_addr));
        printf("wan_ip=%s, in_addr=%s\n", wan_ip,inet_ntoa(addr));
        return 0;
}
#endif