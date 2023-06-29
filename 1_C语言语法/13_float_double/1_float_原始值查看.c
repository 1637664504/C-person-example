#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void dump_hex(const unsigned char *p,int len)
{
    int i;
    char buf[128];
    int ret=0;
    for(i=0;i<len;i++){
        ret += sprintf(buf+ret,"%.2x ",*(p+i));
        if(i%16 == 15 )
        {
            printf("%s\n",buf);
            memset(buf,'\0',ret);
            ret = 0;
        }
    }
    
    if(ret)
        printf("%s\n",buf);
}

int main(void)
{
    float* p;

    float a = 0;
    p = &a;
    dump_hex((uint8_t *)p, sizeof(float));

    float b = 0.0;
    p = &b;
    dump_hex((uint8_t *)p, sizeof(float));
    
    return 0;
}