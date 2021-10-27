#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parse_oneline()
{
    char buf[1024]="123\n234\n345\n";
    //char buf[1024]="123\n234";
    char *p_buf;
    char *p_newlineChar;

    p_buf = buf;
    while((*p_buf != '\0'))
    {
        if(p_newlineChar=strchr(p_buf,'\n'))
        {
            *p_newlineChar='\0';
        }

        printf("%s\n",p_buf);
        if(p_newlineChar)
            p_buf=p_newlineChar+1;
        else
            break;
    }
}

int main ( int argc, char *argv[] )
{
    char buf[64] = "00:50:56:2f:43:d9\n14:6b:9c:bd:46:8d\n";
    char str[32] = {0};
    char *p;
    
    p = buf;
    while(sscanf(p,"%[^\n]", str) > 0)
    {
        printf("str=%s\n",str);
        p += strlen(str)+1;
    }

#if 1
    char *p_buf;
    p_buf = buf;
    while(p=strchr(p_buf,'\n')){
        *p = '\0';
        printf("mac=%s\n",p_buf);
        p_buf=p+1;
    }
#endif
    return 0;
}