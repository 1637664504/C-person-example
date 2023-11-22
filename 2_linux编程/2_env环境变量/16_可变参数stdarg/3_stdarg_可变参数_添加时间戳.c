#include <stdarg.h>
#include <stdio.h>
#include <sys/time.h>

double get_now_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

int my_printf(char* fmt, ...)
{
    char buf[128];
    int ret;
    va_list args;

    ret = snprintf(buf, sizeof(buf), "%f ", get_now_time());
    va_start(args, fmt);
    ret += vsprintf(buf+ret,fmt,args);
    va_end(args);

    buf[ret] = '\n';
    buf[ret + 1] = '\0';
    printf("%s", buf);

    return ret;
}

int main()
{
    my_printf("Hello %s, your age is %d", "John", 30);
    my_printf("%s %d %f", "lilisi",25,3.14);
    return 0;
}
/*
Hello John, your age is 30.
lilisi 25 3.140000
 */