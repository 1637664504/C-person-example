#include <stdio.h>
#include <time.h>

int main(void)
{
    time_t result;
    result = time(NULL);
    printf("date: %ld\n", result);

    return 0;
}