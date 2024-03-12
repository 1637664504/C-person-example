#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    float a = 3.14;
    float b = 3.3333333;
    char buf[256];
    snprintf(buf, sizeof(buf), "%.3f %.5f\n", a, b);
    printf("%s\n", buf);

    return 0;
}

/* 运行结果
3.140 3.33333

 */
