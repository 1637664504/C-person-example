#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char* str = "AAAA*";
    int num;
    sscanf(str, "%x", &num);
    printf("%x\n", num);

    return 0;
}
