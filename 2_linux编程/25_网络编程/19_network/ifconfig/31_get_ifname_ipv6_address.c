#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "common_ipv6.h"

#define _PATH_PROCNET_DEV               "/proc/net/dev"
#define _PATH_PROCNET_IFINET6           "/proc/net/if_inet6"

#define IPV6_ADDR_ANY           0x0000U

#define IPV6_ADDR_UNICAST       0x0001U
#define IPV6_ADDR_MULTICAST     0x0002U
#define IPV6_ADDR_ANYCAST       0x0004U

#define IPV6_ADDR_LOOPBACK      0x0010U
#define IPV6_ADDR_LINKLOCAL     0x0020U
#define IPV6_ADDR_SITELOCAL     0x0040U

#define IPV6_ADDR_COMPATv4      0x0080U

#define IPV6_ADDR_SCOPE_MASK    0x00f0U

#define IPV6_ADDR_MAPPED        0x1000U
#define IPV6_ADDR_RESERVED      0x2000U	/* reserved address space */

struct ipv6_sys_type{
    char prefix[40];
    unsigned short int mask;
    enum IPV6_ADDRESS_TYPE type;
};

struct ipv6_sys_type ipv6_type_array[] = {
	{"fec0",	0xfec0,	IPV6_Site_local},
	{"fe80",	0xfe80,	IPV6_Link_local},
	{"ff00",	0xff00,	IPV6_Multicast},
	{"fd00",	0xfd00,	IPV6_Unique_lolca},
	{"fc00",	0xfc00,	IPV6_Unique_lolca},
	{"2000",	0x2000,	IPV6_Global_unicast},
	{"::1",		0x0000,	IPV6_Lookback},
	{"::ffff::",	0xffff,	IPV6_IPV4_compatible},
};

struct ipv6_address_type_opt{
    enum ipv6_host_inet_type host_type;
    char ip[40];
    struct in6_addr sa;
    enum IPV6_ADDRESS_TYPE ip6_address_type;
};

int get_ipv6_address_type(struct ipv6_address_type_opt *ip6_opt)
{
    int i;
    enum IPV6_ADDRESS_TYPE ret = 0;
    int ipv6_type_max = sizeof(ipv6_type_array)/sizeof(ipv6_type_array[0]);

    if(ip6_opt->host_type == ipv6_address_type_host)
    {
        if((ip6_opt->ip[0] == '\0') || (inet_pton(AF_INET6,ip6_opt->ip,&ip6_opt->sa) != 1))
        {
            return ret;
        }
    }
    else if(ip6_opt->host_type == ipv6_address_type_inet)
    {
        if(inet_ntop(AF_INET6,&ip6_opt->sa,ip6_opt->ip,sizeof(ip6_opt->ip)) == NULL)
        {
            return ret;
        }
    }

    for(i=0;i<ipv6_type_max; i++){
        if((ntohs(ip6_opt->sa.s6_addr16[0]) & ipv6_type_array[i].mask) == ipv6_type_array[i].mask)
        {
            ret = ipv6_type_array[i].type;
            break;
        }
    }
    
    if(ret == IPV6_Lookback)
    {
        if(ip6_opt->sa.s6_addr16[5] == 0xffff)
            ret = IPV6_IPV4_compatible;
        else if(ip6_opt->sa.s6_addr16[6] == 0x0000 && ntohs(ip6_opt->sa.s6_addr16[7]) == 0x0001)
            ret = IPV6_Lookback;
        else
            ret = IPV6_Invalid;
    }
    ip6_opt->ip6_address_type =  ret;

    return ret;
}

void get_interface_ipv6_address(char *ifname)
{
	FILE *f;
	char addr6[40], devname[21];
	struct sockaddr_in6 sap;
	int plen, scope, dad_status, if_idx;
	char addr6p[8][5];

    if(!ifname || strlen(ifname) == 0)
    {
        return;
    }

	f = fopen(_PATH_PROCNET_IFINET6,"r");
	if (f == NULL){
		return;
    }

	while (fscanf
		   (f, "%4s%4s%4s%4s%4s%4s%4s%4s %08x %02x %02x %02x %20s\n",
			addr6p[0], addr6p[1], addr6p[2], addr6p[3], addr6p[4],
			addr6p[5], addr6p[6], addr6p[7], &if_idx, &plen, &scope,
			&dad_status, devname) != EOF
	) {
		if (strcmp(devname, ifname) == 0) {
			sprintf(addr6, "%s:%s:%s:%s:%s:%s:%s:%s",
					addr6p[0], addr6p[1], addr6p[2], addr6p[3],
					addr6p[4], addr6p[5], addr6p[6], addr6p[7]);
			memset(&sap, 0, sizeof(sap));
			inet_pton(AF_INET6, addr6,
					  (struct sockaddr *) &sap.sin6_addr);
			sap.sin6_family = AF_INET6;
			printf("          inet6 addr: %s/%d",
				addr6,
				plen);
			printf(" Scope:");
			switch (scope & IPV6_ADDR_SCOPE_MASK) {
			case 0:
				puts("Global");
				break;
			case IPV6_ADDR_LINKLOCAL:
				puts("Link");
				break;
			case IPV6_ADDR_SITELOCAL:
				puts("Site");
				break;
			case IPV6_ADDR_COMPATv4:
				puts("Compat");
				break;
			case IPV6_ADDR_LOOPBACK:
				puts("Host");
				break;
			default:
				puts("Unknown");
			}
		}
	}
	fclose(f);
}


int main(int argc, char **argv) {

    get_interface_ipv6_address(argv[1]);

    #define test_num 5
    struct ipv6_address_type_opt ip6_opt[test_num];
    char ipv6_test_list[test_num][40]={
        "2409:895a:3206:88dc::7aa",
        "fde5:e7c4:de51::7aa",
        "fe80::a032:75cd:be6b:89dc",
        "::1",
        "::ffff:2345:cdef",
    };

    int i;
    int type;
    for(i=0;i<5;i++)
    {
        strncpy(ip6_opt[i].ip,ipv6_test_list[i],sizeof(ip6_opt[i].ip)-1);
        ip6_opt[i].host_type = ipv6_address_type_host;
        type = get_ipv6_address_type(&ip6_opt[i]);
        printf("pton i=%d,ip=%s,type=%d\n",i,ipv6_test_list[i],type);

        ip6_opt[i].host_type = ipv6_address_type_inet;
        type = get_ipv6_address_type(&ip6_opt[i]);
        printf("ntop i=%d,ip=%s,type=%d\n",i,ipv6_test_list[i],type);
    }
    return 0;
}

