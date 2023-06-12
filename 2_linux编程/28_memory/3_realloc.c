#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char *p = malloc(16);
	strcpy(p,"12345678");

	char *new_p = realloc(p,32);

	printf("p=%s,new_p=%s\n",p,new_p);

	return 0;
}

/*
gdb测试结果:
p=0x5920, *p="12345678"
new_p=0x5920, *new_p="12345678"

结论1:
小字节空间，在原有的基础上扩充


*/
