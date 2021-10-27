#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void test(char *p)
{
    if(p && (p[0] != '\0'))
        printf("p=%s\n",p);
}

int main ( int argc, char *argv[] )
{
    char buf[16]="1234567";
    test(buf);
    return 0;
}