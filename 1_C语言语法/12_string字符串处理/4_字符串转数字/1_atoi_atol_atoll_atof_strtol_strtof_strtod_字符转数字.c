#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char *a="25",
    *b = "123456789",
    *c = "1234567898765",
    *d = "3.1415926";

    // ANSI标准转换
    printf("a=%d\n",atoi(a));
    printf("b=%ld\n",atol(b));
    printf("c=%lld\n",atoll(c));
    printf("d=%f\n",atof(d));


    // C99 / C++11新增
    // 1.转long
    printf("b=%ld\n",strtol(a,NULL,0));
    printf("c=%lld\n",strtoll(d,NULL,0));
    // 转16进制
    char *e="ff";
    printf("e=0x%lx\n",strtol(e,NULL,16));


    // 2.转float double
    printf("d=%f\n",strtof(d,NULL));
    printf("d=%lf\n",strtod(d,NULL));


    return 0;
}
