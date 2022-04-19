#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

enum ip_type_enum {
    IP_INVALID =0,
    IPV4_TYPE_ENUM = 0x1,
    IPV6_TYPE_ENUM = 0x2,
    IP_TYPE_ALL = 0x3
};

//判断地址 ipv4, ipv6 是否是有效的
int IsValidIP(const char *ip, int type)
{
    if (ip == NULL) return 0;

    int result = -1;

    if (type == IPV4_TYPE_ENUM) {
        struct in_addr s;
        result = inet_pton(AF_INET, ip, (void *)&s);

        struct in_addr zero_ip={0};
        if(memcmp(&s,&zero_ip,sizeof(struct in_addr)) == 0)
            result = 0;
    } else if (type == IPV6_TYPE_ENUM) {
        struct in6_addr s;
        result = inet_pton(AF_INET6, ip, (void *)&s);

        struct in6_addr zero_ip6={0};
        if(memcmp(&s,&zero_ip6,sizeof(struct in6_addr)) == 0)
            result = 0;
    }
    return result;
}

int get_ip_type(const char *ip)
{
    int ret = IP_INVALID;
    if(strchr(ip,'.') && (IsValidIP(ip,IPV4_TYPE_ENUM) == 1))
        ret = IPV4_TYPE_ENUM;
    else if(strchr(ip,':') && (IsValidIP(ip,IPV6_TYPE_ENUM) == 1))
        ret = IPV6_TYPE_ENUM;

    return ret;
}

/*
测试 "00:00:00:00:00:00:00:00 是否有效"
*/
void test()
{
    int ret=0;
    char ip6[]="00:00:00:00:00:00:00:00";
    ret = IsValidIP(ip6,IPV6_TYPE_ENUM);
    printf("ret=%d\n",ret);

    char ip4[]="0.0.0.0";
    ret = IsValidIP(ip4,IPV4_TYPE_ENUM);
    printf("ret=%d\n",ret);
}

int main(int argc, char *argv[])
{
    char ip1[64]="2001:4860:4860::8888";
    int ret = 0;
    //ret = get_ip_type(ip1);

    test();
    return 0;
}