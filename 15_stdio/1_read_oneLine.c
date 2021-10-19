#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main ( int argc, char *argv[] )
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
    return 0;
}