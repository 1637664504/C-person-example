
#include "multi_route.h"

int set_route_nat_firewall(char *ifname, int action)
{
    int ret = -1;
    char cmd[256] = {0};
    if(ifname==NULL)
    {
        return -1;
    }

    if(action == 1)
    {
        snprintf(cmd,sizeof(cmd)-1,"iptables -t nat -C POSTROUTING -o %s -j MASQUERADE || iptables -t nat -A POSTROUTING -o %s -j MASQUERADE",ifname,ifname);
        ret = system(cmd);
    }
    else if(action == 0)
    {
        snprintf(cmd,sizeof(cmd)-1,"iptables -t nat -D POSTROUTING -o %s -j MASQUERADE",ifname);
        ret = system(cmd);
    }

    return ret;
}

int del_default_route(struct route_option *opt)
{
    char cmd[256]="";
    
    snprintf(cmd,sizeof(cmd)-1,"ip route del default via %s dev %s",
            opt->getway,opt->ifcname);

    return system(cmd);
}

int set_default_route(struct route_option *opt)
{
    char cmd[256];

    memset(cmd,0,sizeof(cmd));
    snprintf(cmd,sizeof(cmd)-1,"ip route add default via %s dev %s metric %u",
            opt->getway,opt->ifcname,opt->metric);

    memset(cmd,0,sizeof(cmd));
    snprintf(cmd,sizeof(cmd)-1,"iptables -t nat -A POSTROUTING -o %s -j MASQUERADE",
            opt->ifcname);

    return system(cmd);
}
