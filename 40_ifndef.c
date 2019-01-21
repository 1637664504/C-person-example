
#include	<stdlib.h>
#include    <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX 32
#define ONE_TO_ONE_REAL_VITUAL_DEVICE
#define LiuJiang 2
char *route;
int main ( int argc, char *argv[] )
{
#ifndef ONE_TO_ONE_REAL_VITUAL_DEVICE
		printf("liuj-- 111111111\n");
#else 
		printf("liuj-- 222222222\n");
#endif

#ifndef LiuJiang
			printf("liuj-- 3333333\n");
#else 
			printf("liuj-- 4444444\n");
#endif

	return 0;
}


