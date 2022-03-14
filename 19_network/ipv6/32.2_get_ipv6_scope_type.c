#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

enum IPV6_ADDRESS_TYPE{
    IPV6_Invalid = 0,       //not ipv6
    IPV6_Link_local,        //fe80::/10
    IPV6_Global_unicast,    //2000::/3
    IPV6_Unique_lolca,      //fc00::/8, fd00::8
    IPV6_Site_local,        //fec0::/10
    IPV6_Multicast,         //ff00::/8
    IPV6_Lookback,          //::1/128
    IPV6_IPV4_Mapped,       //::192.168.1.1 --> ::xxxx:xxxx
    IPV6_IPV4_compatible,   //::ffff:192.168.1.1 --> ::ffff:xxxx:xxxx
    IPV6_Unspecified,
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
        if()
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
    char ipv6_test_list[][40]={
        "2409:895a:3206:88dc::7aa",
        "fde5:e7c4:de51::7aa",
        "fe80::a032:75cd:be6b:89dc",
        "::1",
        "::ffff:2345:cdef",
        "1762:0:0:0:0:B03:1:AF18",
        "FF01:0:0:0:CA:0:0:2",
        "0:0:0:0:0:0:0:1",
        "0:0:0:0:0:0:0:0",
        "::127.32.67.15",
        "::FFFF:127.32.67.15",
    };

    int i, array_size;
    int type;
    array_size = ARRAY_SIZE(ipv6_test_list)
    for(i=0;i<array_size;i++)
    {
        
    }
    return 0;
}

