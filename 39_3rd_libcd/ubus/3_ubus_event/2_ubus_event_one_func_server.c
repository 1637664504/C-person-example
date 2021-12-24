#include <libubox/uloop.h>
#include <libubox/ustream.h>
#include <libubox/utils.h>
#include <libubus.h>
//#include <json/json.h>
#include <libubox/blobmsg_json.h>

struct blob_buf b;
int main(int argc, char * argv[])
{
    char * path = NULL;
    struct ubus_context * ctx = NULL;
    

    uloop_init();

    ctx = ubus_connect(path);
    if (!ctx)
    {
        printf("ubus connect failed\n");
        return -1;
    }

    printf("connected as %08x\n", ctx->local_id);

    blob_buf_init(&b, 0);

    /* 需要传递的参数 */
    blobmsg_add_u32(&b, "major", 3);
    blobmsg_add_u32(&b, "minor", 56);
    blobmsg_add_string(&b, "name", "mmc01");

    /* 广播名为"add_device"的事件 */
    ubus_send_event(ctx, "add_device", b.head);

    if (ctx)
        ubus_free(ctx);

    return 0;
}
