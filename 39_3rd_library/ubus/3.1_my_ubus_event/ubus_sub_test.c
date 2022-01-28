#include <stdio.h>
#include <stdlib.h>
#include "ubus_sub.h"

#define    UBUS_EVENT_ADD_DEVICE    "add_device"
#define    UBUS_EVENT_REMOVE_DEVICE    "rm_device"
char ubus_event_list[][32]={
    UBUS_EVENT_ADD_DEVICE,
    UBUS_EVENT_REMOVE_DEVICE
};

static void ubus_probe_device_event(struct ubus_context *ctx, struct ubus_event_handler *ev,
              const char *type, struct blob_attr *msg)
{
    char *str;

    if (!msg)
        return;

    /*
    在这里实现收到事件后的动作。
    event也可以传递消息，放在msg中。

    本例子只是将返回的消息打印出来。
    */
    str = blobmsg_format_json(msg, true);
    printf("{ \"%s\": %s }\n", type, str);
    free(str);
}

int main(int argc, char * argv[])
{
    //char * path = NULL;
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

    return 0;
}