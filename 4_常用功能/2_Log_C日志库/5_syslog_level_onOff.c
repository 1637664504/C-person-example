#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
#include <stdarg.h>
#include <errno.h>

#define LOG_TAG "test_log"
int defaultLevel = 6;
#define debugLog(logLevel,format,...) do{ \
        if(logLevel <= defaultLevel)   \
            syslog(logLevel,"[%s:%d]"format"\n",__func__, __LINE__, ##__VA_ARGS__);  \
    }while(0)

#define sysErrLog(format,...) do{ \
        syslog(LOG_ERR,"[%s:%d]"format" . sysError:%d-%s\n",__func__, __LINE__,##__VA_ARGS__,errno,strerror(errno));  \
    }while(0)

void syslog_open()
{
    openlog(LOG_TAG,LOG_PID|LOG_ODELAY,LOG_USER);
}

void syslog_close()
{
    closelog();
}

void help(void)
{
    char progame[32]="test";
    printf("%s function: config wan/wwan route,NAT,arbitrate DNS \n \
    -l: loglevel 0~7\n",
    progame);

    exit(0);
}

void parse_opt(int argc, char *argv[])
{
    char ch;
    while ((ch = getopt(argc, argv, "l:h")) != -1) {
        switch(ch) {
        case 'l':
            defaultLevel = atoi(optarg);
            break;

        case 'h':
        default:
            help();
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    char buf[]="abcd";
    int a=10l;

    parse_opt(argc,argv);
    syslog_open();
    debugLog(LOG_ERR,"buf=%s,a=%d",buf,a);
    debugLog(LOG_DEBUG,"11111111");
    FILE *fp;
    fp = fopen("123.txt","r");
    if(fp == NULL)
        sysErrLog("open file 123.txt failed");
    syslog_close();
    return 0;
}