#include <stdio.h>
#include <time.h>

int main(void)
{
    // 1s = 1000ms = 1000 * 1000us = 1000 * 1000 * 1000ns 
    struct timespec ts = {0};
    double duration = 2.0001;
    ts.tv_sec = (long int)duration;
    ts.tv_nsec = (duration - ts.tv_sec) * 1000000000;
    nanosleep(&ts, NULL);

    return 0;
}