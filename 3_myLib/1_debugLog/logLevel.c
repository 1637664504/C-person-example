#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

enum{
    LogDebug = 0,
    LogInfo,
    LogErr,
}LogLevel;
int debugLevel = 2;
#define debugLog(logLevel,format,...) do{ \
        if(logLevel >= debugLevel)   \
            printf("[%s:%d]"format"\n",__func__, __LINE__, ##__VA_ARGS__);  \
    }while(0)

int main(int argc, char *argv[])
{
    char buf[]="abcd";
    int a=10l;
    debugLevel = 1;
    debugLog(LogDebug,"buf=%s,a=%d",buf,a);
    debugLog(LogInfo,"buf=%s,a=%d",buf,a);
    debugLog(LogErr,"buf=%s,a=%d",buf,a);

    return 0;
}