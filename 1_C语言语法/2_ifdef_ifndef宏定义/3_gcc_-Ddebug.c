/*
gcc -DDEBUG 测试
*/
#include	<stdlib.h>
#include    <stdio.h>

#ifdef DEBUG
#define UNIT_TESTING 1
#endif

int main ( int argc, char *argv[] )
{
    #if UNIT_TESTING
    printf("111\n");
    #else
    printf("222\n");
    #endif

    return 0;
}


/* 测试1:
gcc 3_gcc_-Ddebug.c -DDEBUG
./a.out
111

*/

/* 测试2
gcc 3_gcc_-Ddebug.c
./a.out
222

*/