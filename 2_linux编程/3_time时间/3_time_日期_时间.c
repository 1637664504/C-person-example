#include <stdio.h>
#include <time.h>

int main(void)
{
    time_t result;
    result = time(NULL);
    printf("date: %s\n", asctime(localtime(&result)));

    return 0;
}