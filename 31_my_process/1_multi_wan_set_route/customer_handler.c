#include <common/jrd_common_system.h>
#include <common/jrd_common_event.h>

#define debugLog printf

void send_update_link_metric_event(const char*ifcname,const unsigned int metric)
{
    struct link_route_metric_event event;

    memset(&event,0,sizeof(event));
    strncpy(event.ifcname,ifcname,sizeof(event.interface)-1);
    event.metric = metric;

    jrd_send_event(LINK_ROUTE_METRIC_EVENT,&event,sizeof(event));
}

typedef enum{
    INTERNET_WAN = 0,
    INTERNET_SIM
}INTERNET_TYPE;

#define DEFAULT_PRIMARY_ROUTE_METRIC    100
#define DEFAULT_BACKUP_ROUTE_METRIC     101
struct route_option{
    char ifcname[16];
    char ip[16];
    unsigned int metric;

    unsigned int score;
    unsigned int default_metric;
    INTERNET_TYPE inet_type;

    char old_ifcname[16];
    char old_ip[16];
    unsigned int old_metric;
};
struct route_option g_route_manage[2];

void oem_route_option_init()
{
    g_route_manage[INTERNET_WAN].inet_type = INTERNET_WAN;
    g_route_manage[INTERNET_SIM].inet_type = INTERNET_SIM;
}

void oem_del_default_route(struct route_option *opt)
{
    char cmd[128] = "";

    snprintf(cmd,sizeof(cmd)-1,"ip route del default via %s",opt->old_ip);
    system(cmd);

    memset(cmd,0,sizeof(cmd));
    snprintf(cmd,sizeof(cmd)-1,"ip route del default dev %s",opt->old_ifcname);
}

void oem_set_default_route(struct route_option *opt)
{
    char cmd[128] = "";

    snprintf(cmd,sizeof(cmd)-1,"ip route del default via %s dev %s metric %u",
            opt->ip, opt->ifcname, opt->metric);
    system(cmd);
}

void oem_switch_old_route_info(struct route_option *opt)
{
    strncpy(opt->old_ifcname,opt->ifcname,sizeof(opt->old_ifcname)-1);
    strncpy(opt->old_ip,opt->ip,sizeof(opt->old_ip)-1);
    opt->old_metric = opt->metric;
}

void oem_handler_score_change(struct route_option *opt)
{
    char cmd[128] = "";

    opt->metric = opt->default_metric - opt->score;
    if(opt->metric != opt->old_metric || (strcmp(opt->ip,opt->old_ip) != 0) 
            || (strcmp(opt->ifcname,opt->old_ifcname)))
    {
        debugLog("route change. Old:%s-%s-%u, now=%s_%s_%u\n",opt->old_ifcname,opt->old_ip,opt->old_metric,
            opt->ifcname,opt->ip,opt->metric);

        oem_del_default_route(opt);
        oem_set_default_route(opt);
        oem_switch_old_route_info(opt);
    }
    else
    {
        debugLog("not change");
    }
    
}

void handler_ineteret_capacity(const char* ifcname, const unsigned int score)
{
    
}

int main(int argc, char** argv)
{
    int ret = -1;
    unsigned int score = 0;

    if(argc != 2)
    {
        printf("usage: %s ifcname",argv[0]);
        exit(-1);
    }

    score = detect_link_internet(argv[1]);
    if(score > 0)
        ret = 0;

    printf("ret=%d score=%u",ret,score);
    
    return ret;
}