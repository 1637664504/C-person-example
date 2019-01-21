

#include	<stdlib.h>
#include    <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <asm-generic/ioctls.h>
#define SIOCGIFINDEX	0x8933




#define MAX 32

int main ( int argc, char *argv[] )
{
	char ifcName[1024]="eth2";
	struct ifreq ifr;
	int s = 0;
	
	if (ifcName == NULL) 
	   return -1;
	
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	   return -1;
	strcpy(ifr.ifr_name, ifcName);
	if (ioctl(s, SIOCGIFINDEX, &ifr) < 0) 
	{
	   close(s);
	   return 0;
	}
	close(s);
	printf("%d\n",ifr.ifr_ifindex);


	return 0;
}

