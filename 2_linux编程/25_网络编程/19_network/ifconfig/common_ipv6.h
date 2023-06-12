

enum ipv6_host_inet_type{
    ipv6_address_type_host = 0,
    ipv6_address_type_inet
};

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

