#include <stdio.h>
#include "libxlog.h"
#include "libtime.h"

static struct xLogConfig xconf;

void open_xlog(const char* tag, const struct xLogConfig* config)
{
    openlog(tag,LOG_ODELAY, LOG_USER);
    if (config == NULL) {
        xconf.log_flag = 0;
    }
    else {
        xconf = *config;
    }
}

void xlog(int level, const char* fmt, ...)
{
    char buf[128];
    int ret;
    va_list args;

    ret = snprintf(buf, sizeof(buf), "%f ", get_now_time());
    va_start(args, fmt);
    ret += vsprintf(buf+ret,fmt,args);
    va_end(args);

    buf[ret] = '\n';
    buf[ret + 1] = '\0';

    syslog(level, "%s", buf);
    // send_log(buf);
}

// todo: MQTT,HTTP日志转发
static void send_log(char* buf)
{
}

void close_xlog(void)
{
    closelog();
}
