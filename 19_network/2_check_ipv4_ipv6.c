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

    int result = 0;

    if (type == IPV4_TYPE_ENUM) {
        struct in_addr s;
        result = inet_pton(AF_INET, (char *)ip, (void *)&s);
    } else if (type == IPV6_TYPE_ENUM) {
        struct in6_addr s;
        result = inet_pton(AF_INET6, (char *)ip, (void *)&s);
    }
    return result;
}

int get_ip_type(const char *ip)
{
    int ret = IP_INVALID;
    if(strchr(ip,'.') && (IsValidIP(ip,CHECK_IPV4) == IPV4_TYPE_ENUM))
        ret = IPV4_TYPE_ENUM;
    else if(strchar(ip,':') && (IsValidIP(ip,CHECK_IPV4) == IPV6_TYPE_ENUM))
        ret = IPV6_TYPE_ENUM;

    return ret;
}

int main(int argc, char *argv[])
{
    char pri[64] = {0};
    char sec[64] = {0};
    char dns_file[64] = "1_dns_nameserver.txt";
    jrd_sys_get_nameserver(pri,sec,dns_file);
    printf("%s,%s\n",pri,sec);

    char dns_list[4][64] = {0};
    int ret = 0;
    ret = jrd_sys_get_nameserver_list(dns_list,4,dns_file);
    for(int i=0;i<ret;i++){
        printf("%s\n",dns_list[i]);
    }
    return 0;
}