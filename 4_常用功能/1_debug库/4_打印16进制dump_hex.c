#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void dump_hex(const unsigned char *p,int len)
{
    int i;
    char buf[128];
    int ret=0;
    for(i=0;i<len;i++){
        ret += sprintf(buf+ret,"%0.2x ",*(p+i));
        if(i%15==0 && i)
        {
            printf("%s\n",buf);
            memset(buf,'\0',ret);
            ret = 0;
        }
    }
    
    if(ret)
        printf("%s",buf);
}

int main(void) {

    char a[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
    dump_hex(a,sizeof(a));
    return 0;
}