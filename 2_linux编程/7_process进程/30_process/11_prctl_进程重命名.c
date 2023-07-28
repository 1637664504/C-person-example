#include<stdio.h>
#include<sys/prctl.h>
#include<unistd.h>
#include<string.h>
int main(int argc,char *argv[])
{
    char process_name[] = "test_lilisi";
    memset(argv[0], 0, strlen(argv[0] + 1));
    strncpy(argv[0], process_name, sizeof(process_name));
    prctl(PR_SET_NAME, process_name, NULL, NULL, NULL);
    sleep(100);

    return 0;
}
