#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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


int jrd_get_link_ipv6_address(const char *ifname, enum IPV6_ADDRESS_TYPE type)
{
    char cmd[256] = {0};
    char buf[128] = "2408:8456:3a00:29b:1459:96ff:fe5b:2210/64";
    char address[40] = {0};
    unsigned int prefix_len = 0;
    int ret = -1;

#if 0
    if(!ifname)
        return ret;

    if(type == IPV6_Global_unicast)
    {
        sprintf(cmd,"ifconfig %s |grep Scope:Global |awk '{print $3}'",ifname);
    }
    else
    {
        //To do
        return ret;
    }
      
    if(jrd_system_cmd_call_and_return(cmd,buf,sizeof(buf)) != 0)
    {
        return ret;
    }
#endif
    char *p_str;
    if((strlen(buf) > 16) && (p_str = strchr(buf,'/')))
    {
        *p_str = '\0';
        strncpy(address,buf,sizeof(address)-1);
        prefix_len = atoi(++p_str);
        ret = 0;
    }
    printf("%s, %d\n",address,prefix_len);

    return ret;
}

int main (int argc, char *argv[])
{
    jrd_get_link_ipv6_address("eth1",2);
    return 0;
}
