#ifndef sys_link_h
#define sys_link_h

typedef enum link_status{
    LINK_INVALID = 0,
    LINK_UP,
    LINK_DOWN,
    LOWER_UP,
}E_LINK_STATUS;

int get_link_ip(char *ifcname, char *ip, unsigned int len);
int get_link_addr(const char *ifc_name, struct in_addr *addr);
int get_link_mac(char *ifcname, unsigned char *mac, unsigned int len);

#endif