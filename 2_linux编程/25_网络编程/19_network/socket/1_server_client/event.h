#ifndef _event_h_
#define _event_h_

#define EVENT_SOCKET_NAME "test_unix_sock"

enum event_program{
    EVENT_PROGRAM_MONITOR = 0,
    EVENT_PROGRAM_WAN_LAN,
    EVENT_PROGRAM_MULTI_WAN,
    EVENT_PROGRAM_MAX
};

enum PROGRAM_MONITOR{
    PROGRAM_REGISTER_EVENT = 0,
    PROGRAM_UNREGISTER_EVENT,
};

struct info_monitor{
    enum PROGRAM_MONITOR event_type;
    enum event_program program;
};

typedef enum{
    LAN_ADAPTION_EV = 0,
    WAN_ADAPTION_EV
}wan_lan_adaption_e;

struct info_wan_lan{
    char ifcname[16];
    wan_lan_adaption_e adapt;
};

struct info_mutil_wan{
    char ifcname[16];
    unsigned int score;
    char back_ifcname[16];
    unsigned int back_score;
};

struct event_msg{
    enum event_program program;
    void *info;
};

#endif
