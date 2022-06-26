#include <stdio.h>
int main(void)
{
#ifdef TEST_DEBUG
    printf("111\n");
#endif
	printf("222\n");
	return 0;
}

/*
cmd:
make
./a.out

result:
111
222
*/