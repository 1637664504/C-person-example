#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main()
{
    char data[16] = "RE: hello world";
    char* p1 = &data[4];
    memmove(data, p1, strlen("hello world"));

    return 0;
}

/*gdb 调试
hello worldorld
 */
