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
int h_proto=20;
uint16_t hdr_p[8]={1,2,3,4,5,6,7,8};
hexdump()
{
	char buf[1024]={0};
	int len=0,j=0;

	len = sprintf(buf, "Rx h_proto 0x%04x :",(uint16_t) ntohs(h_proto) );

	for (j =0 ;j<8;j++)
	  len += sprintf(buf+len," 0x%4x,",(uint16_t) ntohs(*((uint16_t*)hdr_p+j)) );
	printf("%s log done\n",buf);
}

int main(int argc , const char* argv[])
{
	hexdump();
	return 0;
}

