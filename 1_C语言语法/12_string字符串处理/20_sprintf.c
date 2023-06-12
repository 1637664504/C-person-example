#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define JRD_REDIREECT_SCRIPT "/jrd-resource/bin/dns_redirect_rule.sh"
void jrd_set_redirect(int enable)
{
    char cmd[128] = {0};
    if(enable)
    {
        sprintf(cmd,JRD_REDIREECT_SCRIPT" add");
    }
    else
    {
        sprintf(cmd,JRD_REDIREECT_SCRIPT" del");
    }

    printf("cmd=%s \n");
    //jrd_system_cmd_call(cmd);
}
int main ( int argc, char *argv[] )
{
    jrd_set_redirect(1);
    return 0;
}