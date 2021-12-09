#ifndef sys_link_h
#define sys_link_h

int get_link_ip(char *ifcname, char *ip, unsigned int len);
int get_link_addr(const char *ifc_name, struct in_addr *addr);

#endif