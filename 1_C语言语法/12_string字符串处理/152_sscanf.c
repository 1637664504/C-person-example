#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char buf[128] = "D2:22:33:44:55:61\nD2:22:33:44:55:62\n";
    char one_line[32];
    int i = 0;
    char *p = buf;

    while((*p != '\0') && (sscanf(p, "%[^\n]", one_line) > 0))
    {
        printf("%d:=%s\n",i,one_line);

        //Parse next line
        if(p = strchr(p,'\n'))
        {
            p++;
        }
        else
        {
            break;
        }
    }
 
    return 0;
}