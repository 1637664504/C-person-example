#include <stdio.h>
#include <string.h>

void dump_hex_whithName(const unsigned char *hex, const unsigned int hex_len,const char *hex_name)
{
    char buf[128];
    int i;
    int len = 0;

    for(i=0;i<hex_len;i++)
    {
        len += sprintf(buf+len,"%.2x ",*(unsigned char*)(hex+i));

        if(i%16 == 15)
        {
            len = 0;
            printf("%s=%s \n",hex_name,buf);
            memset(buf,'\0',sizeof(buf));
        }
    }
    if(i%16 != 15)
        printf("%s=%s \n",hex_name,buf);
}

void dump_hex(const unsigned char *hex, const unsigned int hex_len)
{
    char buf[128];
    int i;
    int len = 0;

    for(i=0;i<hex_len;i++)
    {
        len += sprintf(buf+len,"%.2x ",*(unsigned char*)(hex+i));

        if(i%16 == 15)
        {
            len = 0;
            printf("==%s \n",buf);
            memset(buf,'\0',sizeof(buf));
        }
    }

    if(i%16 != 15)
        printf("==%s \n",buf);
}

int main(int argc, char* const argv[])
{
    unsigned char buf[]={0,0x1,0x2,0x3,4,5,6,7,8,9,11,12,13,14,15,16,17,18};
    dump_hex(buf,sizeof(buf));
    return 0;
}