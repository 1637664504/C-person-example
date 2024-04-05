#include <stdarg.h>
#include <stdio.h>

int my_printf(const char* format, ...)
{
    char buf[128];
    int ret;
    va_list args;

    va_start(args, format);
    ret = vsprintf(buf,format, args);
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