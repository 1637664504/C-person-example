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
    if(strchr(ip,'.') && (IsValidIP(ip,IPV4_TYPE_ENUM) == 1))
        ret = IPV4_TYPE_ENUM;
    else if(strchr(ip,':') && (IsValidIP(ip,IPV6_TYPE_ENUM) == 1))
        ret = IPV6_TYPE_ENUM;

    return ret;
}

//方法1: 设置ipv4, ipv6 dns
#define NAMESERVER_FILE "32_dns.conf"
void manual_set_nameserver_with_ipv6(const char *pri, const char *sec,
        const char *ipv6_pri, const char *ipv6_sec)
{
    char cmd[256] = {0};
    int len = 0;

    if(pri && IsValidIP(pri,IPV4_TYPE_ENUM))
        len += sprintf(cmd+len,"nameserver %s\n",pri);
    if(sec && IsValidIP(sec,IPV4_TYPE_ENUM))
        len += sprintf(cmd+len,"nameserver %s\n",sec);
    if(ipv6_pri && IsValidIP(ipv6_pri,IPV6_TYPE_ENUM))
        len += sprintf(cmd+len,"nameserver %s\n",ipv6_pri);
    if(ipv6_sec && IsValidIP(ipv6_sec,IPV6_TYPE_ENUM))
        len += sprintf(cmd+len,"nameserver %s\n",ipv6_sec);

    printf( "liuj 65 dns=%s len=%d\n",cmd,len);
    FILE *fp = fopen(NAMESERVER_FILE, "w");
    if (fp == NULL)
    {
        return;
    }

    fwrite(cmd, 1, len, fp);
    fclose(fp);
}

void test1(void)
{
    char dns[4][40]={"223.5.5.5","8.8.8.8",
        "2400:3200::1","2400:3200:baba::1"};
    manual_set_nameserver_with_ipv6(dns[0],dns[1],dns[2],dns[3]);
}

int main(int argc, char *argv[])
{
#if 0
    char dns_list[4][64] = {0};
    int ret = 0;
    ret = jrd_sys_get_nameserver_list(dns_list,4,dns_file);
    for(int i=0;i<ret;i++){
        printf("%s\n",dns_list[i]);
    }
#endif
    test1();
    return 0;
}