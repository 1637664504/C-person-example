#ifndef _multi_oem_h_
#define _multi_oem_h_

unsigned int get_link_oem_config_metric(const char *ifcname);
int oem_fill_route_option(struct route_option *opt,const char *ifcname,unsigned int score);

#endif
