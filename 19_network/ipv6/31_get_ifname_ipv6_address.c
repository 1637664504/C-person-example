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

struct if_inet6{
    char ip6_str[40];
    struct in6_addr ipv6addr;
    int ifindex;
    int prefixlen;
    int scope;
    char devname[16];
};

struct if_inet6_opt{
    char ifname[16];
    int result_num;
    struct if_inet6 result_list[12];
};

 int get_if_inet6_with_opt(struct if_inet6_opt *opt)
 {
    FILE *f;
    char addr6[40], devname[21];
    struct sockaddr_in6 sap;
    int plen, scope, dad_status, if_idx, i;
    char addr6p[8][5];

    if(!opt || strlen(opt->ifname) == 0)
    {
        return -1;
    }

    f = fopen(_PATH_PROCNET_IFINET6,"r");
    if (f == NULL){
        return -1;
    }

    int ret = 0;
    i = 0;
    while (fscanf
           (f, "%4s%4s%4s%4s%4s%4s%4s%4s %08x %02x %02x %02x %20s\n",
            addr6p[0], addr6p[1], addr6p[2], addr6p[3], addr6p[4],
            addr6p[5], addr6p[6], addr6p[7], &if_idx, &plen, &scope,
            &dad_status, devname) != EOF
    ) {
        if (strcmp(devname, opt->ifname) == 0) {
            sprintf(addr6, "%s:%s:%s:%s:%s:%s:%s:%s",
                    addr6p[0], addr6p[1], addr6p[2], addr6p[3],
                    addr6p[4], addr6p[5], addr6p[6], addr6p[7]);

            scope = scope & IPV6_ADDR_SCOPE_MASK;
            switch(opt->expect_scope){
                case IPV6_Global_unicast:
                    if(scope == 0)
                        ret = 1;

                    break;
                case IPV6_Link_local:
                    if(scope == IPV6_ADDR_LINKLOCAL)
                        ret = 1;
                    
                    break;
                case IPV6_Site_local:
                    if(scope == IPV6_ADDR_SITELOCAL)
                        ret = 1;
                    
                    break;
                case IPV6_IPV4_compatible:
                    if(scope == IPV6_ADDR_COMPATv4)
                        ret = 1;
                    
                    break;
                case IPV6_Lookback:
                    if(scope == IPV6_ADDR_LOOPBACK)
                        ret = 1;
                    break;
            }

            if(ret)
            {
                opt->result_list[i].ifindex=if_idx;
                opt->result_list[i].prefixlen=plen;
                opt->result_list[i].scope=scope;
                strncpy(opt->result_list[i].ip6_str,addr6,sizeof(opt->result_list[i].devname)-1);
                strncpy(opt->result_list[i].devname,devname,sizeof(opt->result_list[i].devname)-1);
                inet_pton(AF_INET6, addr6, (struct sockaddr *) &opt->result_list[i].ipv6addr);
                opt->result_num ++;
                ret = 0;
            }
        }
    }
    fclose(f);
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

int main(int argc, char **argv)
{
    char ifname[16]="";
    if(argc != 2)
        strcpy(ifname,"eth1");
    else
        strncpy(ifname,argv[1],sizeof(ifname));
    get_interface_ipv6_address(ifname);

    //test 2
    struct if_inet6_opt opt =
    {
        .ifname = "eth1",
        .expect_scope = IPV6_Global_unicast,
        .result_num = 0,
    };
    
    get_if_inet6_with_opt(&opt);
    return 0;
}

