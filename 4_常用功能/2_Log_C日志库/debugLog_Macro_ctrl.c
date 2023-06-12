#include<stdio.h>
#ifdef DEBUG
//#define debugLog(format,...) if(debugFlag) { printf("%s-%s-%d: "format, __FILE__, __func__, __LINE__, ##__VA_ARGS__);}
#define debugLog(format,...) { printf("%s-%s-%d: "format, __FILE__, __func__, __LINE__, ##__VA_ARGS__);}
#else
#define debugLog(format,...)
#endif

int main()
{
    debugLog("1111");

    return 0;
}