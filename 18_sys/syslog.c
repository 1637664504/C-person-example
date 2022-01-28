#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <stdarg.h>

int main (int argc, char *argv[])
{
    openlog("liuj",LOG_PID|LOG_ODELAY,LOG_USER);
    syslog(LOG_NOTICE,"123456abcdef\n");
    closelog();
    return EXIT_SUCCESS;
}