
#include <arpa/inet.h>

#define _PATH_PROCNET_DEV               "/proc/net/dev"
#define _PATH_PROCNET_IFINET6           "/proc/net/if_inet6"

enum ipv6_host_inet_type{
    ipv6_address_type_host = 0,
    ipv6_address_type_inet
};

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

enum IPV6_ADDRESS_TYPE{
    IPV6_Invalid = 0,       //not ipv6
    IPV6_Link_local,        //fe80::/10
    IPV6_Site_local,        //fec0::/10
    IPV6_Multicast,         //ff00::/8
    IPV6_Unique_lolca,      //fc00::/8, fd00::8
    IPV6_Global_unicast,    //2000::/3
    IPV6_Lookback,          //::1/128
    IPV6_IPV4_Mapped,       //::192.168.1.1 --> ::xxxx:xxxx
    IPV6_IPV4_compatible,   //::ffff:192.168.1.1 --> ::ffff:xxxx:xxxx
};

struct ipv6_address_type_opt{
    enum ipv6_host_inet_type host_type;
    char ip[40];
    struct in6_addr sa;
    enum IPV6_ADDRESS_TYPE ip6_address_type;
};

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
    int expect_scope;
    int result_num;
    struct if_inet6 result_list[12];
};


