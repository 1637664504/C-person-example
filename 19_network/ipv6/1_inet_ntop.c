#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
int test_inet_pton(char *ip6_addr,struct in6_addr *dst)
{
    
    if(!dst || !ip6_addr || strlen(ip6_addr)==0)
        return -1;

    return inet_pton(AF_INET6,ip6_addr,dst);
}

int test_inet_ntop(struct in6_addr *src,char *ip6_addr,unsigned int len)
{
    int ret = -1;

    if(!src || !ip6_addr)
        return -1;

    if(inet_ntop(AF_INET6,src,ip6_addr,len))
        ret = 0;

    return ret;
}

int main()
{
    struct in6_addr address;
    int ret;
    ret = test_inet_pton("2409:895a:3206:88dc:11a3:d4d7:3871:2ab5",&address);
    printf("ret=%d\n",ret);

    char ip6_str[40];
    test_inet_ntop(&address,ip6_str,sizeof(ip6_str));
    //char *p;
    //p = inet_ntop(AF_INET6,&address,ip6_str,sizeof(ip6_str));
    printf("ret=%d,ip=%s\n",ret,ip6_str);

    return 0;
}
