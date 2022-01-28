#ifndef _ubus_sub_h_
#define _ubus_sub_h_

#include <libubus.h>
#include <libubox/blobmsg_json.h>
#include "ubus_pub.h"

struct ubus_sub_handle{
    struct ubus_context * ctx;
    char * path;
};

struct ubus_subscribe{
    void (*handle_callback)(struct ubus_context *ctx, struct ubus_event_handler *ev,const char *type, struct blob_attr *msg);
    unsigned int event_list_count;
    char (*event_list)[32];
};

int ubus_subscribe_register_events(struct ubus_subscribe *subscribe);
int ubus_subscribe_init(struct ubus_sub_handle *handle);
void ubus_subscribe_free(struct ubus_sub_handle *handle);

#endif