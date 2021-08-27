
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
    fprintf(fp,"1111_2222");
 
    fclose(fp);
    return 0;
}