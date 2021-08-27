
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char file[16]="/tmp/123";
    FILE *fp=NULL;
    if((fp=fopen(file,"w")) == NULL)
    {
        perror("fopen file failed");
        exit(-1);
    }

    int a=123;
    fprintf(fp,"abc=%d\n",a);
    fprintf(fp,"def=%d\n",a);
    fclose(fp);
    return 0;
}