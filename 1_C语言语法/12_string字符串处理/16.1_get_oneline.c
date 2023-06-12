#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char *get_oneline(char *dst, char *src, unsigned n)
{
    int len;
    char *p_src = src;

    if(!dst && !src && !len)
        return NULL;

    while(*p_src && (*p_src != '\n')){
        p_src++;
    }
    //Must set len. Avoid long copies
    if((len = p_src-src) > n)
        len = n;

    strncpy(dst,src,len);

    return p_src;
}

char *get_oneline_set_nextline(char *dst, char *src, unsigned n, char *next)
{
    int len;
    char *p_src = src;

    if(!dst && !src && !len && !next)
        return NULL;

    while(*p_src && (*p_src != '\n')){
        p_src++;
    }
    //Must set len. Avoid long copies
    if((len = p_src-src) > n)
        len = n;

    strncpy(dst,src,len);

    next = p_src;
    if(*++next == '\0')
        next = NULL;

    return p_src;
}

int main ( int argc, char *argv[] )
{
    char buf[128] = "D2:22:33:44:55:61\nD2:22:33:44:55:62\n";
    char oneline[64] = {0};
    char *p_buf = buf;
    #if test
    while(p_buf = get_oneline(oneline,p_buf,sizeof(oneline)-1))
    {
        printf("buf=%s\n",oneline);
        memset(oneline,'\0',sizeof(oneline));
        if(*++p_buf == '\0')
            break;
    }
    #endif

    char *next;
    p_buf = buf;
    while(get_oneline_set_nextline(oneline,p_buf,sizeof(oneline)-1,next))
    {
        printf("buf=%s\n",oneline);
        memset(oneline,'\0',sizeof(oneline));
        if(next)
            p_buf = next;
    } 

    return 0;
}