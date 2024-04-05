#pragma once
#include <stdarg.h>
#include <syslog.h>
#include <stdint.h>

// #define LOG_SYSLOG 0x1
#define LOG_HTTP 0x2
#define LOG_MQTT 0x4

struct xLogConfig {
    uint32_t log_flag;
};

#define xlog_debug(fmt, ...) xlog(LOG_DEBUG,"%s:%d <debug> "fmt,__func__, __LINE__, ##__VA_ARGS__)
#define xlog_info(fmt, ...) xlog(LOG_INFO,"%s:%d <info> "fmt,__func__, __LINE__, ##__VA_ARGS__)
#define xlog_err(fmt, ...) xlog(LOG_ERR,"%s:%d <err> "fmt,__func__, __LINE__, ##__VA_ARGS__)

void open_xlog(const char* tag, const struct xLogConfig* config);
void xlog(int level, const char* fmt, ...);
void close_xlog(void);
