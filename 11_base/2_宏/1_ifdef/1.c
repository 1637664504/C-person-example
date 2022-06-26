#include <stdio.h>
int main(void)
{
#ifndef ROOT_PATH
#define ROOT_PATH "123"
#endif
	printf("%s\n",ROOT_PATH);

	return 0;
}
