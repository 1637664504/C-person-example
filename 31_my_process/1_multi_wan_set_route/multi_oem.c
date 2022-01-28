#include <string.h>

#define PRIMARY_METRIC 100
#define SECOND_METRIC 101
unsigned int oem_get_link_metric(const char *ifcname)
{
    unsigned int metric = 0;
    if(strncmp(ifcname,"eth",3) || strncmp(ifcname,"ppp",3))
    {
        metric = PRIMARY_METRIC;
    }
    else
    {
        metric = SECOND_METRIC;
    }

    return metric;
}

int oem_fill_route_option(struct route_option *opt,const char *ifcname,unsigned int score)
{
    strcpy(opt->ifcname,ifcname,sizeof(opt->ifcname)-1);
    strcpy(opt->ip,"192.168.30.2",sizeof(opt->ip)-1);
    //strcpy(opt->ipv6,"192.168.30.2",sizeof(opt->ipv6)-1);
    opt->metric = oem_get_link_metric() - score;

    return 0;
}
