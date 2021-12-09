#include "common/network/network.h"

void* judge_wan_interface(void *argv)
{
    struct in_addr addr;
    char *ifcname = NULL;
    char ip[16]="";

    get_link_ip(ifcname,ip,sizeof(ip)-1);
    printf("ip=%s\n",ip);

    return NULL;
}

#if 1
int main(void)
{
    judge_wan_interface
}
#endif