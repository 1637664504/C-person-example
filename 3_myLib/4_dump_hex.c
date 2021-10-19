#include <stdio.h>
#include <stdlib.h>

void dump_hex(const unsigned char *p,int len)
{
    int i;
    char buf[512];
    int ret=0;
    for(i=0;i<len;i++){
        ret += sprintf(buf+ret,"%x:",*(p+i));
    }
    printf("hex=%s",buf);
}

int main(void) {

    char a[8]={1,2,3,4,5};
    dump_hex(a,4);
    return 0;
}