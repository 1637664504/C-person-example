
/*
测试宏定义 对 #if, #ifdef的影响

*/
#include <stdio.h>

#define fun1
#define fun2 1
#define fun3 0
int main ( int argc, char *argv[] )
{
/*  compile error
#if fun1
    printf("111\n");
#endif
*/

#ifdef fun1
    printf("222\n");
#endif

#if fun2
    printf("333\n");
#endif

#ifdef fun2
    printf("444\n");
#endif

#if fun3
    printf("555\n");
#endif

#ifdef fun3
    printf("666\n");
#endif

    return 0;
}