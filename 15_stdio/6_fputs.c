#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char buf[256]={0};
    char dns[4][40]={"223.5.5.5","8.8.8.8","2400:3200:baba::1"};
    int i;
    int len=0;
    for(i=0; i<4; i++)
    {
        if(dns[i][0] != '\0'){
            //strcat(buf,dns[i]);
            len+=sprintf(buf+len,"%s\n",dns[i]);
        }
    }
    printf("buf=%s\n",buf);

    FILE *fp = fopen("123.txt", "w");
    if (fp == NULL)
    {
        return -1;
    }

    fwrite(buf, 1, len, fp);
    fclose(fp);

  return 0;
}