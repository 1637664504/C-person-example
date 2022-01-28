#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#define NAMESERVER_FILE	    "resolv.conf"
void manual_set_nameserver(const char nameserver_list[][64],unsigned int list_size)
{
    char buf[256];
    unsigned int i;
    FILE *fp = fopen(NAMESERVER_FILE, "w");

    memset(buf,'\0',sizeof(buf));
    for(i=0;i<list_size;i++)
    {
        if(strlen(nameserver_list[i]))
            fprintf(fp,"nameserver %s\n",nameserver_list[i]);
    }
    fclose(fp);
}

int main(void)
{
    char dns[4][64]={"223.5.5.5","8.8.8.8","8.8.4.4"};
    manual_set_nameserver(dns,4);
}