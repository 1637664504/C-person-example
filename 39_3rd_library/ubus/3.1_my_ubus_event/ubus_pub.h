#ifndef _ubus_pub_h_
#define _ubus_pub_h_

#include <libubus.h>
#include <libubox/blobmsg_json.h>

struct ubus_pub_handle{
    struct ubus_context * ctx;
    char * path;
};

struct ubus_pub_info{
    char event_name[32];
    struct blob_buf b;
};

int ubus_pub_event_init(struct ubus_pub_handle *handle);
void ubus_pub_event_free(struct ubus_pub_handle *handle);
void ubus_pub_event_send_msg(struct ubus_pub_handle *handle,struct ubus_pub_info *info);

#endif