#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#include "xlog.h"

FILE *xlog_fp;
int xlog_init(void)
{
    xlog_fp=fopen(LIUJ_LOG_FILE,"a+");
    if(xlog_fp == NULL){
        printf("fopen file %s failed --",LIUJ_LOG_FILE);
        return -1;
    }
}

void xlog_close()
{
    if(xlog_fp)
        fclose(xlog_fp);
}

//#define xloge(format, args...) {char buf[246];sprintf(buf,format,args);system}
#define xloge(format,args...) do{ char buf[128]; char cmd[128];\
    sprintf(buf,format,args);sprintf(cmd,"echo %s >> /tmp/xloge.log",buf);system(cmd);}while(0)

#if 1
int main()
{
    xlog_init();
    xlogf("aaa=%d\n",123);
    //fprintf(xlog_fp,"aaa=%d\n",123);
    xlog_close();

    //xloge("bbb=%d",234);
    return 0;
}
#endif