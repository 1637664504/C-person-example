#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int jrd_sys_get_link_mac(char *ifc_name, unsigned char *mac)
{
    int sock = 0;
    struct ifreq ifr = {0};

    if (ifc_name == NULL || mac == NULL)
    {
        return -1;
    }

    if(sock = socket(AF_INET, SOCK_DGRAM, 0) < 0)
    {
        printf("create sock fail; %s\n",strerror(errno));
        return -1;
    }

    strcpy(ifr.ifr_name, ifc_name);
    if (ioctl(sock, SIOCSIFHWADDR, &ifr) <  0)
    {
        printf("ioctl get addr fail: %s\n",strerror(errno));
        return -1;
    }
    memcpy(mac, ifr.ifr_hwaddr.sa_data, IFHWADDRLEN);

    return 0;
}

int main()
{
	unsigned char mac[6];
	jrd_sys_get_link_mac("eth1",mac);
	printf("Interface eth2: %.2x:%.2x:%.2x: %.2x:%.2x:%.2x\n",
            //*mac, *(mac+1), *(mac+2), *(mac+3), *(mac+4), *(mac+5));
            mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
	return 0;
}
