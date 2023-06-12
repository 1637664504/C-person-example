#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAMESERVER_FILE "123.txt"

void jrd_oem_append_nameserver_to_resolv(const char *nameserver)
{
    char buf[128] = {0};
    int len;
    //FILE *fp = fopen(NAMESERVER_FILE, "a+");
    FILE *fp = fopen(NAMESERVER_FILE, "a");
    if (fp == NULL)
    {
        return;
    }

    len = snprintf(buf, sizeof(buf), "nameserver %s\r\n", nameserver);
    fwrite(buf, 1, len, fp);
    fclose(fp);
}

int main ( int argc, char *argv[] )
{
    char dns[40]="2400:3200:baba::1";
    jrd_oem_append_nameserver_to_resolv(dns);
    return 0;
}