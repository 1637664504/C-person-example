#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strchr_count(char *src,int c)
{
    int count = 0;
    char *p = src;
    while(*p)
    {
        if(*p++ == c)
            count++;
    }

    return count;
}

void jrd_router_ipv6_fill_address(char *address, char *dst)
{
    char ipv6_front[40] = {0};
    char ipv6_tail[40] = {0};
    char ipv6_blank[40] = {0};
    char tmp[40] = {0};
    int count;
    int i=0;
    char *p_separator;

    strncpy(tmp,address,39);
    p_separator = strstr(tmp,"::");
    if(p_separator)
    {
        count = strchr_count(tmp,':');
        for(i=0;i<8-count;i++)
        {
            strcat(ipv6_blank,"0000:");
        }

        *(++p_separator) = '\0';
        strcat(ipv6_front,tmp);
        strcat(ipv6_tail,p_separator+1);
        snprintf(dst,40,"%s%s%s",ipv6_front,ipv6_blank,ipv6_tail);
    }
}

void jrd_router_ipv6_get_prefix_address(char *address,int prefix, char *prefix_address)
{
    char ipv6_slice[8][5]={0};
    char tmp[40]={0};

    if(strstr(address,"::"))
    {
        jrd_router_ipv6_fill_address(address,tmp);
    }
    else
    {
        strncpy(tmp,address,39);
    }
    //sscanf(tmp,"%4s:%4s:%4s:%4s:%4s:%4s:%4s:%4s",ipv6_slice[0],ipv6_slice[1],ipv6_slice[2],ipv6_slice[3],ipv6_slice[4],ipv6_slice[5],ipv6_slice[6],ipv6_slice[7]);
    sscanf(tmp,"%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]",ipv6_slice[0],ipv6_slice[1],ipv6_slice[2],ipv6_slice[3],ipv6_slice[4],ipv6_slice[5],ipv6_slice[6],ipv6_slice[7]);

    int i,n,m;
    unsigned short hex = 0;
    int len = 0;

    n=prefix/16;
    m=prefix%16;
    for(i=0;i<n;i++)
    {
        len+=sprintf(prefix_address+len,"%s:",ipv6_slice[i]);
    }

    if(m)
    {
        char *p_end;
        hex=strtol(ipv6_slice[n], &p_end, 16);
        hex = hex & (0xffff<<(16-m));

        sprintf(prefix_address+len,"%4x:",hex);
    }

    printf("ip=%s n=%d,m=%d,hex=%x\n",prefix_address,n,m,hex);
}

int main(int argc, char *argv[])
{
    char addr[256] = "240e:47c:30a8:7fee:16af:f622:90cf:8477";
    char addr2[256] = "2408:8557:3031:2339::e484";
    int prefix = 64;
    char prefix_address[40];
    jrd_router_ipv6_get_prefix_address(addr,prefix,prefix_address);
    jrd_router_ipv6_get_prefix_address(addr2,prefix,prefix_address);
    //jrd_router_ipv6_fill_address(addr2,prefix_address);
    return 0;
}