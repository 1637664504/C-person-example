#include <stdio.h>
int add(int a,int b)
{
    return a+b;
}

int fun_add(void *arg)
{
    int (*fun)(int a,int b);
    fun = arg;
    int s;
    s = fun(3,5);

    printf("s=%d\n",s);

    return s;
}

int main()
{
    fun_add((void *)add);
    return 0;
}