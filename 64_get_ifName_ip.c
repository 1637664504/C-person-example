#include <stdio.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int get_ip(char *ifname,char *ip)
{
	int sock;
	struct sockaddr_in sin;
	struct ifreq ifr;

	sock = sock(AF_INET，SOCK_DGRAM,0);
}

int main(int argc , const char* argv[])
{

	return 0;
}
