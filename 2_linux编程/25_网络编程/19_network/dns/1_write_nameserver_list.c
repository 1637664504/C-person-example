#include <stdio.h>
#include <string.h>

#define NAMESERVER_FILE	    "resolv.conf"
void sys_network_set_nameserver(const char nameserver_list[][64],unsigned int list_size)
{
    unsigned int i;
    FILE *fp = fopen(NAMESERVER_FILE, "w");

    for(i=0;i<list_size;i++)
    {
        if(strlen(nameserver_list[i]))
            fprintf(fp,"nameserver %s\n",nameserver_list[i]);
    }
    fclose(fp);
}

int main(void)
{
    char dns[4][64]={"223.5.5.5","8.8.8.8","2001:4860:4860::8888","2001:4860:4860::8844"};
    sys_network_set_nameserver(dns,4);
}