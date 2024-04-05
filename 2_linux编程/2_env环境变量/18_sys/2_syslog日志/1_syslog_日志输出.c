#include <syslog.h>

#define LOG_TAG "liuj"
int main (int argc, char *argv[])
{
    openlog(LOG_TAG, LOG_PID | LOG_ODELAY, LOG_USER);
    syslog(LOG_NOTICE,"hello syslog");
    syslog(LOG_NOTICE, "[%s:%d]123456abcdef", __func__, __LINE__);
    closelog();

    return 0;
}

/*
Nov 21 17:01:24 zero liuj[14681]: hello ssylog
Nov 21 17:01:24 zero liuj[14681]: [main:8]123456abcdef
*/