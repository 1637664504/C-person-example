#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "common_ipv6.h"

int get_interface_ipv6_address(struct if_inet6_opt *opt)
{
    FILE *f;
    char addr6[40], devname[21];
    struct sockaddr_in6 sap;
    int plen, scope, dad_status, if_idx;
    int i = 0;
    char addr6p[8][5];

    if(!opt || strlen(opt->ifname) == 0)
    {
        return -1;
    }

    f = fopen(_PATH_PROCNET_IFINET6,"r");
    if (f == NULL){
        return -1;
    }
    
    while (fscanf
           (f, "%4s%4s%4s%4s%4s%4s%4s%4s %08x %02x %02x %02x %20s\n",
            addr6p[0], addr6p[1], addr6p[2], addr6p[3], addr6p[4],
            addr6p[5], addr6p[6], addr6p[7], &if_idx, &plen, &scope,
            &dad_status, devname) != EOF
    ) {
        if (strcmp(devname, opt->ifname) == 0) {
            sprintf(addr6, "%s:%s:%s:%s:%s:%s:%s:%s",
                    addr6p[0], addr6p[1], addr6p[2], addr6p[3],
                    addr6p[4], addr6p[5], addr6p[6], addr6p[7]);
            memset(&sap, 0, sizeof(sap));
            inet_pton(AF_INET6, addr6,(struct sockaddr *) &sap.sin6_addr);
            sap.sin6_family = AF_INET6;

            opt->result_list[i].ifindex = if_idx;
            opt->result_list[i].prefixlen = plen;
            opt->result_list[i].scope = scope & IPV6_ADDR_SCOPE_MASK;
            memcpy(&opt->result_list[i].ipv6addr,  &sap.sin6_addr, sizeof(opt->result_list[i].ipv6addr));
            strncpy(opt->result_list[i].ip6_str,addr6,sizeof(opt->result_list[i].ip6_str)-1);
            opt->result_num ++;
            i++;
        }
    }
    fclose(f);

    return i;
}


int main(int argc, char **argv)
{
    char ifname[16]="";
    if(argc != 2)
        strcpy(ifname,"eth1");
    else
        strncpy(ifname,argv[1],sizeof(ifname));
    struct if_inet6_opt opt={
        .ifname = "eth1",
    };
    get_interface_ipv6_address(&opt);
    int i=0;
    for(i=0;i<opt.result_num;i++)
    {
        printf("%s:%d %s\n",__func__,__LINE__,opt.result_list[i].ip6_str);
    }

    return 0;
}