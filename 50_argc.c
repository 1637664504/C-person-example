#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int i;
	
	printf("liuj-- argc=%d\n",argc);
	for(i=0;i<=argc;i++)
	{
		printf("liuj-- %d %s\n",i,argv[i]);
	}

    return 0;
}

