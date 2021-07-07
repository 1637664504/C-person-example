#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main()
{
        int inet_sock={0};
        char wan_ip[64]={0};
        struct ifreq ifr;
        inet_sock = socket(AF_INET, SOCK_DGRAM, 0);
 
        strcpy(ifr.ifr_name, "eth2");
        //SIOCGIFADDR标志代表获取接口地址
        if (ioctl(inet_sock, SIOCGIFADDR, &ifr) <  0)
                perror("ioctl");
        strncpy(wan_ip,inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr),64);
        printf("wan_ip=%s\n", wan_ip);
        return 0;
}