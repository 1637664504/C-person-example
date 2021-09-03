#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

enum mac_type{
    raw_mac_type=0,
    string_mac_type,
};

int get_link_mac_by_ifname(const char *ifname, char *data, enum mac_type type)
{
        int inet_sock={0};
        struct ifreq ifr;
        //struct mac_addr;
        unsigned char mac[IFHWADDRLEN]={0};
        inet_sock = socket(AF_INET, SOCK_DGRAM, 0);
 
        strcpy(ifr.ifr_name, "eth2");
        //SIOCGIFADDR标志代表获取接口地址
        if (ioctl(inet_sock, SIOCGIFHWADDR, &ifr) <  0)
                perror("ioctl");

        
        memcpy(mac, ifr.ifr_hwaddr.sa_data, IFHWADDRLEN);
        if(type == raw_mac_type)
                printf("1111");
        else if(type ==  string_mac_type)
        printf("Interface eth2: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
            //*mac, *(mac+1), *(mac+2), *(mac+3), *(mac+4), *(mac+5));
            mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
}

int main()
{
        char mac[64]="";
        get_link_mac_by_ifname("eth1",mac,string_mac_type);
        return 0;
}