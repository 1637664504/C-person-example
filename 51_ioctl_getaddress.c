#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>


int main(int argc, char *argv[])
{
	struct ifreq ifr;
	int s = 0;
	char ifcName[64]="eth0";
	
	if (ifcName == NULL)
	   return -1;
	
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	   return -1;
	strcpy(ifr.ifr_name, ifcName);
	if (ioctl(s, SIOCGIFADDR, &ifr) < 0)
	{
		
		printf("liuj-- ioctl failed\n");
	   close(s);
	   return 0;
	}
	close(s);
	struct sockaddr_in *sin = (struct sockaddr_in*) &ifr.ifr_addr;
	char ip[16]={0};
	
	inet_ntop(AF_INET, &sin->sin_addr.s_addr, ip, 16);
    printf("SIOCGIFADDR:%s\n", ip);
	return 0;

}

