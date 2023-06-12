#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void help(void)
{
    char progame[32]="jrd_sharemem_test";
    printf("%s              dump all share_mem \n \
            %s -m module:   dump module share_mem \n \
            module: \n \
            AP: lan wan wifi vpn fota time ap_usage\n \
            MODULE: wwan voice sms sim mw module_usage \n\
            Example: %s -m lan \n \
            -f save info to file",
            progame,progame,progame);

    //exit(-1);
}

int main ( int argc, char *argv[] )
{
    int ch;
    char file[64]={0};
    char module[16]={0};
    int all = 1;

    while ((ch = getopt(argc, argv, "m:f:h")) != -1) {
        switch(ch) {
        case 'm':
            strncpy(module,optarg,sizeof(module)-1);
            all = 0;
            break;

        case 'f':
            strncpy(file,optarg,sizeof(file)-1);
            break;

        case 'h':
        default:
            help();
            break;
        }
    }

    return 0;
}