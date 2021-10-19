#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define DNS_FILE "9_dns.txt"
#define LEN_128 128


int main ( int argc, char *argv[] )
{
    FILE *fp;

    if((fp=fopen(DNS_FILE,"r")) == NULL)
    {
        printf("Open file %s failed: %s\n",DNS_FILE,strerror(errno));
        exit(-1);
    }

    char buf[LEN_128] = {0};
    char *p = NULL;
    while(fgets(buf,LEN_128,fp)){
        #if 0
        if(p = strstr(buf,"nameserver")){
            printf("%s\n",buf+strlen("nameserver")+1);
        }
        //末尾多一个 \n
        #endif
        sscanf(buf,"nameserver %s\n",buf);
        printf("%s\n",buf);
    }
    return 0;
}