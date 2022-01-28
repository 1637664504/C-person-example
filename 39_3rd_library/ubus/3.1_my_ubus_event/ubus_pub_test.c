#include <unistd.h>
#include "ubus_pub.h"

struct ubus_pub_handle g_handle;

void send_ubus_pub_event_msg(struct ubus_pub_handle *handle)
{
    struct ubus_pub_info info={0};
    char event_name[]="add_device";

    strcpy(info.event_name,event_name);

    blob_buf_init(&info.b, 0);
    blobmsg_add_u32(&info.b, "major", 3);
    blobmsg_add_u32(&info.b, "minor", 56);
    blobmsg_add_string(&info.b, "name", "mmc01");
    ubus_pub_event_send_msg(handle,&info);
    blob_buf_free(&info.b);
}

int main()
{
    //struct pub_ubus_event event = {0};
    ubus_pub_event_init(&g_handle);
    send_ubus_pub_event_msg(&g_handle);
    ubus_pub_event_free(&g_handle);

    return 0;
}
