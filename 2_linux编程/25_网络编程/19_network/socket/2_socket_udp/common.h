#define JRD_EVENT_PORT  39678
#define JRD_EVENT_IP    "127.0.0.1"

enum jrd_events_type{
    WAN_CHANGE_EVENT = 0,
};

struct wan_change_event{
    char interface[16];
    int status;
};

struct jrd_event_msg{
    enum jrd_events_type event;
    //unsigned int len;
    void *info;
};