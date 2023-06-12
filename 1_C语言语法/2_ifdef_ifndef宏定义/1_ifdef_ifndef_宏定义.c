#include <stdio.h>
int main(void)
{
#ifndef ROOT_PATH
	printf("111\n");
#else
	printf("222\n");
#endif
	

	return 0;
}
/*
gcc 1.c -DROOT_PATH="234"
222

gcc 1.c -DROOT_PATH
222

gcc 1.c
111

 */
