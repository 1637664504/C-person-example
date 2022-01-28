#ifndef _multi_route_h_
#define _multi_route_h_

enum INET_TYPE{
    INET_IPv4 = 0,
    INET_IPv6,
};

struct route_option{
    char ifcname[16];
    char getway[16];
    char mask[16];
    char ipv6_getway[40];
    char ipv6_prefix[40];
    unsigned int metric;
};

#endif
