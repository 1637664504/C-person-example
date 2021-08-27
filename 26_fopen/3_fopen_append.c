
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char file[16]="/tmp/123";
    FILE *fp=NULL;
    if((fp=fopen(file,"a")) == NULL)
    {
        perror("fopen file failed");
        exit(-1);
    }

    fprintf(fp,"%s:123\n","aaaa");
 
    fclose(fp);
    return 0;
}