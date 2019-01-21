

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
#define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))


int main(int argc , const char* argv[])
{
	int a;
	a= KERNEL_VERSION(2,6,0);
	printf("a=%d\n",a);
	return 0;
}


