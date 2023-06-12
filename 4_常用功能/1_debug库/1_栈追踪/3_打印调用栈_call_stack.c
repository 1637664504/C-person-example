/*
打印函数名:
-g -rdynamic

*/

#include <stdio.h>
#include <execinfo.h>

#define STACK_SIZE 32
void printStack(void)
{
    void *trace[STACK_SIZE];
	size_t size = backtrace(trace, STACK_SIZE);
    printf("size=%u\n", size);
	char **symbols = (char **)backtrace_symbols(trace,size);
	size_t i = 0;
	for(; i<size; i++)
	{
		printf("%d--->%s\n", i, symbols[i]);
	}
	return;
}

void fun3(void)
{
    printf("3333\n");
    printStack();
}

void fun2(void)
{
    printf("2222\n");
    fun3();
}

void fun1(void)
{
    printf("11111\n");
    fun2();
}

int main ( int argc, char *argv[] )
{
    fun1();

    return 0;
}
