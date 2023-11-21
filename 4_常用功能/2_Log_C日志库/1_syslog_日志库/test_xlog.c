#include <stdio.h>
#include "libxlog.h"

int main(int argc, char* argv[])
{
    open_xlog("test", NULL);
    xlog_debug("%d %s %f", 18, "lilisi", 50.2);
    xlog_info("%d %s %f", 18, "lilisi", 50.2);
    xlog_err("%d %s %f", 18, "lilisi", 50.2);
    close_xlog();

    return 0;
}