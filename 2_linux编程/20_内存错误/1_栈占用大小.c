#include <stdio.h>
int main(void)
{
    int a1 = 1;
    char buf[64] = {0};
    int a2 = 2;

    getchar();
    printf("stack size: %ld\n", &a1 - &a2);
}