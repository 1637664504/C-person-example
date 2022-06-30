#include <stdio.h>
#include <execinfo.h>

#define MAX_DEPTH 20
void PrintfStackFunName(void)
{
	void *buff[MAX_DEPTH] = { 0 };
	unsigned int depth = backtrace(buff, MAX_DEPTH);
	char **funName = backtrace_symbols(buff, depth);
	for (int i = 0; i < MAX_DEPTH; i++) {
		if (i >= depth) {
			break;
		}
		printf("i =  %d, func = %s\n", i, funName[i]);
	}

	//未释放funName 内存
}

void func4(void)
{
	printf("%s [line] = %d\n", __FUNCTION__, __LINE__);
	PrintfStackFunName();
}

void func3(void)
{
	printf("%s [line] = %d\n", __FUNCTION__, __LINE__);
	func4();
}

void func2(void)
{
	printf("%s [line] = %d\n", __FUNCTION__, __LINE__);
	func3();
}

void func1(void)
{
	printf("%s [line] = %d\n", __FUNCTION__, __LINE__);
	func2();
}
int main(void)
{
	func1();
	return 0;
}

/*
编译:
gcc backtrace.c -rdynamic

运行:
func1 [line] = 38
func2 [line] = 32
func3 [line] = 26
func4 [line] = 20
i =  0, func = ./a.out(PrintfStackFunName+0x45) [0x562aa6d99a4f]
i =  1, func = ./a.out(func4+0x26) [0x562aa6d99b13]
i =  2, func = ./a.out(func3+0x26) [0x562aa6d99b3c]
i =  3, func = ./a.out(func2+0x26) [0x562aa6d99b65]
i =  4, func = ./a.out(func1+0x26) [0x562aa6d99b8e]
i =  5, func = ./a.out(main+0x9) [0x562aa6d99b9a]
i =  6, func = /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xe7) [0x7f516f8f1c87]
i =  7, func = ./a.out(_start+0x2a) [0x562aa6d9992a]

*/