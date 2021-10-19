#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char *get_oneline(char *oneline,unsigned int len,char *str)
{
    char *p = str;
    char *p_newlineChar;
    char *result = NULL;
    if((*p != '\0') && (p_newlineChar = strchr(p,'\n')))
    {
        strncpy(oneline,str,p_newlineChar-p);
        result = p_newlineChar+1;
    }
    else
    {
        strncpy(oneline,str,p_newlineChar-p);
        result = NULL;
    }

    return result;
}

int main ( int argc, char *argv[] )
{
    char buf[128] = "D2:22:33:44:55:61\nD2:22:33:44:55:62\n";
    char oneline[64] = {0};
    char *p = buf;
    while(p = get_oneline(p,64,buf))
    {
        printf("buf=%s..\n",oneline);
    }
    

    return 0;
}