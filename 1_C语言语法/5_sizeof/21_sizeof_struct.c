
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct stu{
    char name[64];
    int age;
};
int main ( int argc, char *argv[] )
{
    struct stu AA[2];
    printf("AA sizeof=%d\n",sizeof(AA));

    return 0;
}