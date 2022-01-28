#include <libubox/uloop.h>
#include <libubox/ustream.h>
#include <libubox/utils.h>
#include <libubus.h>
//#include <json/json.h>
#include <libubox/blobmsg_json.h>
#include "ubus_pub.h"

void ubus_pub_event_send_msg(struct ubus_pub_handle *handle,struct ubus_pub_info *info)
{
    /* Broadcase event */
    ubus_send_event(handle->ctx, info->event_name, info->b.head);
}

int ubus_pub_event_init(struct ubus_pub_handle *handle)
{
    uloop_init();
    handle->ctx = ubus_connect(handle->path);
    if (!handle->ctx)
    {
        printf("ubus connect failed\n");
        return -1;
    }
    printf("connected as %08x\n", handle->ctx->local_id);

    return 0;
}

void ubus_pub_event_free(struct ubus_pub_handle *handle)
{
    if (handle->ctx)
        ubus_free(handle->ctx);
}
