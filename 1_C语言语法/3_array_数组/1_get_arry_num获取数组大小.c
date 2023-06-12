#include <stdio.h>
int main()
{
    char buf[][16]={
        "aaa"
    };
    int num = sizeof(buf)/sizeof(buf[0]);
    return 0;
}