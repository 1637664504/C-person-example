#include <stdio.h>
#include <unistd.h>

int main(void)
{
    unsigned long  time = 10;
    // 1s = 1000ms = 1000 * 1000us
    // usleep()--微秒为单位
    usleep(time * 1000);

    return 0;
}