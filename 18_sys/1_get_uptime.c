#include <stdio.h>
#include <sys/sysinfo.h>

int main()
{
    struct sysinfo s_info;
    sysinfo(&s_info);
    printf("up_time=%d",s_info.uptime);

    return 0;
}