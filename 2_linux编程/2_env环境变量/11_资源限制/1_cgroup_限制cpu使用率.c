#include <stdio.h>

void test_cpu()
{
    printf("thread: test_cpu start\n");
    int total = 0;
    while (1) {
        ++total;
    }
}

int main()
{
    test_cpu();
    return 0;
}
