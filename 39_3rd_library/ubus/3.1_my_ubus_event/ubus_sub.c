#include <libubox/uloop.h>
#include <libubox/ustream.h>
#include <libubox/utils.h>
#include <libubus.h>
//#include <json/json.h>
#include <libubox/blobmsg_json.h>

#include "ubus_sub.h"

static struct ubus_context * ctx = NULL;
static const char * cli_path;

int ubus_subscribe_register_events(struct ubus_subscribe *subscribe)
{
    static struct ubus_event_handler listener;
    int ret = 0;

    /* 注册特定event的listener。多个event可以使用同一个listener */
    memset(&listener, 0, sizeof(listener));
    listener.cb = subscribe->handle_callback;

    int i;
    for(i=0;i<subscribe->event_list_count;i++)
    {
        ret = ubus_register_event_handler(ctx, &listener, subscribe->event_list[i]);
        if (ret)
        {
            fprintf(stderr, "register %s event failed.\n",subscribe->event_list[i]);
            return -1;
        }
    }

    return 0;
}

static void ubus_add_fd(void)
{
    ubus_add_uloop(ctx);

#ifdef FD_CLOEXEC
    fcntl(ctx->sock.fd, F_SETFD,
        fcntl(ctx->sock.fd, F_GETFD) | FD_CLOEXEC);
#endif
}

static void ubus_reconn_timer(struct uloop_timeout *timeout)
{
    static struct uloop_timeout retry =
    {
        .cb = ubus_reconn_timer,
    };
    int t = 2;

    if (ubus_reconnect(ctx, cli_path) != 0) {
        uloop_timeout_set(&retry, t * 1000);
        return;
    }

    ubus_add_fd();
}

static void ubus_connection_lost(struct ubus_context *ctx)
{
    ubus_reconn_timer(NULL);
}

int ubus_subscribe_init(struct ubus_sub_handle *handle)
{
    uloop_init();
    cli_path = handle->path;

    ctx = ubus_connect(handle->path);
    if (!ctx)
    {
        printf("ubus connect failed\n");
        return -1;
    }

    printf("connected as %08x\n", ctx->local_id);
    ctx->connection_lost = ubus_connection_lost;

    handle->ctx = ctx;

    ubus_add_fd();

    return 0;
}

void ubus_subscribe_free(struct ubus_sub_handle *handle)
{
    if (handle->ctx)
        ubus_free(handle->ctx);
}
