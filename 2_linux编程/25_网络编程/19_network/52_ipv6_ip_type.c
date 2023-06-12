#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

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
};

struct _ipv6_type{
    char prefix[40];
    unsigned int prefixlen;
    enum IPV6_ADDRESS_TYPE type;
};

static struct _ipv6_type ipv6_type[] = {
    {"fe80",    3,  IPV6_Link_local},
    {"2000",    1,  IPV6_Global_unicast},
    {"fc00",    2,  IPV6_Unique_lolca},
    {"fd00",    2,  IPV6_Unique_lolca},
    {"fec0",    3,  IPV6_Site_local},
    {"ff00",    2,  IPV6_Multicast},
    {"::1",     3,  IPV6_Lookback},
};

int get_ipv6_address_type(const char *ip)
{
    struct in6_addr s = {0};
    int ret = IPV6_Invalid;
    int i;

    if(ip == NULL)
        return ret;
    
    ret = inet_pton(AF_INET6, (char *)ip, (void *)&s);
    if(ret != 1)
        return ret;

    int ipv6_type_num = sizeof(ipv6_type)/sizeof(struct _ipv6_type);
    for(i=0; i<ipv6_type_num; i++)
    {
        if(strncmp(ip, ipv6_type[i].prefix, ipv6_type[i].prefixlen) == 0)
        {
            ret = ipv6_type[i].type;
            break;
        }
    }
    printf("ip=%s, type=%d\n",ip, ret);

    return ret;
}

int main(int argc, char *argv[])
{
    char addr[40] = "2408:8557:3031:2339:16a9:7548:be65:e484";
    char addr2[40] = "fe80::a875:eeff:fef7:34d1";
    char addr3[40] ="fd57:24e:754a::1";
    get_ipv6_address_type(addr);
    get_ipv6_address_type(addr2);
    get_ipv6_address_type(addr3);
    return 0;
}