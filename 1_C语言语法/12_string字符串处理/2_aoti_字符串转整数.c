#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char buf[32] = "123";
    int num = atol(buf);

    printf("num=%d\n", num);

    return 0;
}
