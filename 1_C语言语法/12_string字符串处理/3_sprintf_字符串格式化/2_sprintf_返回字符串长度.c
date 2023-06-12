#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char buf[64] = { 0 };
    int ret;
    ret = sprintf(buf, "123 %d %s", 555, "liuj");
    printf("ret=%d, buf=%s, len=%ld \n", ret, buf, strlen(buf));

    return EXIT_SUCCESS;
}

