#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <stdarg.h>

#define LOG_TAG "test_log"
int main (int argc, char *argv[])
{
    openlog(LOG_TAG,LOG_PID|LOG_ODELAY,LOG_USER);
    syslog(LOG_NOTICE,"[%s:%d]123456abcdef",__func__,__LINE__);
    closelog();

    return 0;
}