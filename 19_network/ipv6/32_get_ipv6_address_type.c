#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include "common_ipv6.h"

struct ipv6_sys_type{
    char prefix[40];
    unsigned short int mask;
    enum IPV6_ADDRESS_TYPE type;
};

static struct ipv6_sys_type ipv6_type_array[] = {
	{"fec0",	0xfec0,	IPV6_Site_local},
	{"fe80",	0xfe80,	IPV6_Link_local},
	{"ff00",	0xff00,	IPV6_Multicast},
	{"fd00",	0xfd00,	IPV6_Unique_lolca},
	{"fc00",	0xfc00,	IPV6_Unique_lolca},
	{"2000",	0x2000,	IPV6_Global_unicast},
	{"::1",		0x0000,	IPV6_Lookback},
	{"::ffff::",	0xffff,	IPV6_IPV4_compatible},
};

int get_ipv6_address_type(struct ipv6_address_type_opt *ip6_opt)
{
    int i;
    enum IPV6_ADDRESS_TYPE ret = 0;

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

    int ipv6_type_max = sizeof(ipv6_type_array)/sizeof(ipv6_type_array[0]);
    for(i=0; i<ipv6_type_max; i++){
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

int main(int argc, char **argv)
{
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

