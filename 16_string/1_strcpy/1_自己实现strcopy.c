/*
自己实现strcpy
*/

#include <stdlib.h>
#include <stdio.h>

#define way1 0
#define way2 1
#define way3 0

char *my_strcopy(char *dst, const char *src)
{
	if(!src || !dst)
		return NULL;

#if way1
	for(; *src; src++,dst++)
	{
		*dst=*src;
	}
	*dst = '\0';
#elif way2
	while(*src)
	{
		*dst++ = *src++;
	}
	*dst = '\0';
#elif way3
	while((*dst++ = *src++))
		;
#endif
	

	return src;
}

int main ( int argc, char *argv[] )
{
	char a[16]="12345678";
	char b[16];
	my_strcopy(b,a);
	return 0;
}

