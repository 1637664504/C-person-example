#include <unistd.h>
#include "ubus_pub.h"
#include "ubus_sub.h"

char ubus_event_list[][32]={
    UBUS_EVENT_ADD_DEVICE,
    UBUS_EVENT_REMOVE_DEVICE
};

struct ubus_sub_handle handle;
void recv_msg()
{
    struct ubus_sub_handle handle;

    /* 连接ubusd */
    if (UBUS_STATUS_OK != ubus_subscribe_init(&handle))
    {
        printf("ubus connect failed!\n");
        return -1;
    }

    struct ubus_subscribe subscribe = {0};
    subscribe.handle_callback = ubus_probe_device_event;
    subscribe.event_list_count = sizeof(ubus_event_list)/sizeof(ubus_event_list[0]);
    subscribe.event_list = ubus_event_list;
    ubus_subscribe_register_events(&subscribe);

    uloop_run();
    ubus_subscribe_free(&handle);
}


void send_msg()
{

}

int main()
{
    //1.recv msg
    recv_msg()
    
    return 0;
}