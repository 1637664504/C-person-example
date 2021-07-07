

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main ( int argc, char *argv[] )
{
    char buf[32];
    int len = 0;
    FILE *fp;

    #if 0
    len = fread(buf,1,512,stdin);
    printf("len=%s buf=%s\n",len,buf);
    #endif
    fp = fopen("data","r");
    if(!fp){
        perror("open file \"data\" fail ");
        return -1;
    }
    len = fread(buf,1,32,fp);
    if(feof(fp)){
        printf("need continue read file\n");
    }
    printf("len=%d buf=%s\n",len,buf);

    return 0;
}

