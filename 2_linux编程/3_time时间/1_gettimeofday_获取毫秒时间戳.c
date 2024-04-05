#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

void get_format_time_ms(char* str_time)
{
    struct tm* tm_t;
    struct timeval time;

    gettimeofday(&time, NULL);
    tm_t = localtime(&time.tv_sec);
    if (NULL != tm_t) {
        sprintf(str_time, "%04d-%02d-%02d_%02d.%02d.%02d.%03ld",
            tm_t->tm_year + 1900,
            tm_t->tm_mon + 1,
            tm_t->tm_mday,
            tm_t->tm_hour,
            tm_t->tm_min,
            tm_t->tm_sec,
            time.tv_usec / 1000);
    }

    return;
}

int main(int argc, char* argv[])
{
    char buf[128];
    get_format_time_ms(buf);
    printf("%s\n", buf);
    return 0;
}
