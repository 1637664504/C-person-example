#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <common/jrd_common_system.h>
#include <common/jrd_common_event.h>
#include <jrd_sys_platform.h>

#define JRD_LAN_BRIDGE "br-lan"

static void jrd_bridge_add_link(const char*bridge, const char*link)
{
    char cmd[128] = {0};

    sprintf(cmd,"ifconfig %s 0.0.0.0",link);
    jrd_system_cmd_call(cmd);

    memset(cmd,'\0',sizeof(cmd));
    sprintf(cmd,"brctl addif %s %s",bridge,link);
    jrd_system_cmd_call(cmd);
}

static void jrd_bridge_del_link(const char*bridge, const char*link)
{
    char cmd[128] = {0};

    sprintf(cmd,"brctl delif %s %s",bridge,link);
    jrd_system_cmd_call(cmd);
}

static void send_wan_change_event(const char*ifcname,link_status_e status,wan_lan_adaption_e adaption)
{
    struct wan_change_event event;

    memset(&event,0,sizeof(event));
    strncpy(event.interface,ifcname,sizeof(event.interface)-1);
    event.status = status;
    event.adaption = adaption;

    jrd_send_event(WAN_CHANGE_EVENT,&event,sizeof(event));
}

void jrd_adaption_set_lan(const char *ifcname)
{
    jrd_bridge_add_link(JRD_LAN_BRIDGE,ifcname);
    jrd_system_cmd_call("/jrd-resource/bin/wan_conn.sh disconn");
    send_wan_change_event(ifcname,LINK_UP_EV,LAN_ADAPTION_EV);
}

void jrd_adaption_set_wan(const char *ifcname)
{
    jrd_bridge_del_link(JRD_LAN_BRIDGE,ifcname);
    jrd_system_cmd_call("/jrd-resource/bin/wan_conn.sh conn");
    send_wan_change_event(ifcname,LINK_UP_EV,WAN_ADAPTION_EV);
}

void jrd_adaption_set_down(const char *ifcname)
{
    send_wan_change_event(ifcname,LINK_DOWN_EV,LAN_ADAPTION_EV);
}