#include <stddef.h>
#include <sys/time.h>
#include "libtime.h"

double get_now_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}