#include <stdio.h>
#include <unistd.h>

#ifdef DEBUG
unsigned int debugFlag = 1;
#else
unsigned int debugFlag = 0;
#endif
#define debugLog(format,...) do{if(debugFlag) printf("[%s:%d]"format,__func__, __LINE__, ##__VA_ARGS__);}while(0)

void help(void)
{
    char progame[32]="multi_wan";
    printf("%s [-d] \
            option: \
            -d : Enable DebugLog \
            ",
            progame);
}

int main(int argc, char *argv[])
{
    char ch;
    while ((ch = getopt(argc, argv, "d")) != -1) {
        switch(ch) {
        case 'd':
            debugFlag = 1;
            break;
        default:
            help();
            break;
        }
    }

    char buf[64]="111111";
    int a = 10;
    debugLog("buf=%s, a=%d\n",buf,a);

    return 0;
}