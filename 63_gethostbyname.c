#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
  
  int main ( int argc, char *argv[] )
  {
	struct hostent *hostinfo;
	struct in_addr pptp_server_addr;
	char pptp_server[16]="4455liu";
	char pptp[64]={0};
	int ipv6_count=0;
	hostinfo=gethostbyname(argv[1]);
	if (!hostinfo)
	{
		printf("PPTP: Unknown host %s\n", pptp_server);
		return -1;
	}
	pptp_server_addr = *(struct in_addr*)hostinfo->h_addr;
	inet_ntop(AF_INET,&pptp_server_addr,pptp,sizeof(pptp));
	printf("pptp=%s\n",pptp);

	while(* hostinfo->h_addr_list){
		memset(pptp,0,64);
		if(hostinfo->h_addrtype == AF_INET){
			pptp_server_addr = *(struct in_addr*)hostinfo->h_addr_list;
			inet_ntop(AF_INET,&pptp_server_addr,pptp,sizeof(pptp));
			printf("pptp=%s\n",pptp);
			hostinfo->h_addr_list++;
		}else if(hostinfo->h_addrtype == AF_INET6){
			ipv6_count++;
//			printf("ipv6_count =%d ipv6=%s\n",ipv6_count,inet_ntop(hostinfo->h_addrtype,,pptp,sizeof(pptp)));
		}
		sleep(1);
	}

	return 0;
  }

