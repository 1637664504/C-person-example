/*
参考busybox ifconfig实现
*/

#include <stdio.h>
#include <string.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

#define IPV4_LEN 16
int main(int argc, char *argv[])
{
    struct sockaddr_in *addr;
    //1.init ifreq
    char name[IF_NAMESIZE]="eth1";
    struct ifreq ifr;
    memset(&ifr,0,sizeof(ifr));
    strcpy(ifr.ifr_name,name);

    //2.init socket
    int sock;
    sock = socket(AF_INET,SOCK_DGRAM,0);

    //3.获取 ip
    if(ioctl(sock,SIOCGIFADDR,&ifr) == -1)
        perror("ioctl error.");
    addr = (struct sockaddr_in*)&(ifr.ifr_addr);
    //inet_ntoa 线程安全函数
    char *ip = inet_ntoa(addr->sin_addr);
    printf("ip=%s\n",ip);

    //4.获取 广播
    if(ioctl(sock,SIOCGIFBRDADDR,&ifr) == -1)
        perror("ioctl error.");
    addr = (struct sockaddr_in*)&(ifr.ifr_broadaddr);
    char *broadaddr = inet_ntoa(addr->sin_addr);
    printf("ip=%s\n",broadaddr);

    //5.获取 netmask
    if(ioctl(sock,SIOCGIFNETMASK,&ifr) == -1)
        perror("ioctl error.");
    addr = (struct sockaddr_in*)&(ifr.ifr_broadaddr);
    char *netmask = inet_ntoa(addr->sin_addr);
    printf("ip=%s\n",netmask);

    //5.获取 hwaddr
    if(ioctl(sock,SIOCGIFHWADDR,&ifr) == -1)
        perror("ioctl error.");
    unsigned char hw[6];
    memcpy(hw,ifr.ifr_hwaddr.sa_data,6);
    printf("HWaddr: %02X:%02X:%02X:%02X:%02X:%02X\n", hw[0], hw[1], hw[2], hw[3], hw[4], hw[5]);

    //6.获取 flags
    if(ioctl(sock,SIOCGIFFLAGS,&ifr) == -1)
        perror("ioctl error.");
    printf("flags=0x%x\n", ifr.ifr_flags);

    //6.获取 MTU
    if(ioctl(sock,SIOCGIFMTU,&ifr) == -1)
        perror("ioctl error.");
    printf("mtu=%u\n", ifr.ifr_mtu);

    return 0;
}