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

int sys_get_nameserver(char *pri, char *sec, const char *dns_file)
{
    char buf[128] = {0};
    char resolv_conf[64] = "/etc/resolv.conf";
    FILE *fp;
    int i = 0;

    if(dns_file)
    {
        strncpy(resolv_conf,dns_file,64);
    }

    if((fp=fopen(resolv_conf,"r")) == NULL)
    {
        printf("Open file %s failed:\n",resolv_conf);
        return 0;
    }

    while(fgets(buf,sizeof(buf),fp))
    {
        if(strstr(buf,"nameserver"))
        {
            //if(jrd_system_is_ip(buf))
            {
                if(i == 0)
                {
                    sscanf(buf,"nameserver %s\n",pri);
                }
                else if(i == 1)
                {
                    sscanf(buf,"nameserver %s\n",sec);
                }
                i++;
            }
        }
    }

    return i;
}

int sys_get_nameserver_list(char (*dns_list)[64], int num, const char *dns_file, int type)
{
    char buf[128] = {0};
    char resolv_conf[64] = "/etc/resolv.conf";
    char address[64] = {0};
    int address_type;
    FILE *fp;
    int i = 0;

    if(dns_file)
    {
        strncpy(resolv_conf,dns_file,64);
    }

    if((fp=fopen(resolv_conf,"r")) == NULL)
    {
        printf("Open file %s failed:\n",resolv_conf);
        return 0;
    }

    while(fgets(buf,sizeof(buf),fp))
    {
        if(strstr(buf,"nameserver"))
        {
            if(sscanf(buf,"nameserver %s\n",address))
            {

                address_type = get_ip_type(address);
                //ipv4 and ipv6 type
                if(address_type & type)
                {
                    strcpy(dns_list[i],address);
                    i++;
                }
                else if(address_type == type)
                {
                    strcpy(dns_list[i],address);
                    i++;
                }
                else if(address_type == type)
                {
                    strcpy(dns_list[i],address);
                    i++;
                }
            }
        }
    }

    return i;
}

int main(int argc, char *argv[])
{
    char pri[64] = {0};
    char sec[64] = {0};
    char dns_file[64] = "1_dns_nameserver.txt";
    sys_get_nameserver(pri,sec,dns_file);
    printf("%s,%s\n",pri,sec);

    char dns_list[4][64] = {0};
    int ret = 0;
    ret = sys_get_nameserver_list(dns_list,4,dns_file,IPV4_TYPE_ENUM);
    for(int i=0;i<ret;i++){
        printf("%s\n",dns_list[i]);
    }
    return 0;
}