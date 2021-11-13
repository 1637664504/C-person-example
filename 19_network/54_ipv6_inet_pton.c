#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>


void dump_ipv6_hex(struct in6_addr *addr)
{
    for(int i=0;i<16;i+=2){
        printf("%02x%02x:",addr->s6_addr[i],addr->s6_addr[i+1]);
    }
    printf("\n");
}

int get_ipv6_address(const char *ip)
{
    struct in6_addr s = {0};
    int ret = 0;
    int i;
    char buf[64]={0};
    const char *p = NULL;

    if(ip == NULL)
        return ret;
    
    ret = inet_pton(AF_INET6, (char *)ip, (void *)&s);
    if(ret != 1)
        return ret;

    dump_ipv6_hex(&s);

    s.s6_addr[7]+=1;
    p = inet_ntop(AF_INET6,(void *)&s, buf, sizeof(buf)-1);
    printf("new_ipv6=%s",buf);

    return ret;
}

int main(int argc, char *argv[])
{
    char addr[40] = "2408:8557:3031:2339:16a9:7548:be65:e484";
    char addr2[40] = "fe80::a875:eeff:fef7:34d1";
    char addr3[40] ="fd57:24e:754a::1";

    get_ipv6_address(addr);
    return 0;
}