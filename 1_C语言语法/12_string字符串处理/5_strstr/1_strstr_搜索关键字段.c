#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int handler_wifi(const char* cmd)
{
    char buf[128] = { 0 };
    char wifi[32] = { 0 };
    char pass[32] = { 0 };
    char* p_start = buf;
    char* p_end = buf;

    // cmd=WIFI,ruichi-liuj,ij2200862;
    strncpy(buf, cmd, sizeof(buf) - 1);
    p_start = strstr(buf, "WIFI,")+5;
    p_end = strchr(p_start, ',');
    strncpy(wifi, p_start, p_end - p_start);

    // pass
    p_start = p_end+1;
    p_end = strchr(p_start, ';');
    strncpy(pass, p_start, p_end - p_start);
    printf("%s,%s\n", wifi, pass);

    return 0;
}

int main(int argc, char* argv[])
{
    char buf[128] = "WIFI,ruichi-liuj,ij2200862;";
    handler_wifi(buf);

    return 0;
}
