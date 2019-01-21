#include	<stdlib.h>
#include    <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

int main ( int argc, char *argv[] )
{
	int ret;
	ret =system(argv[1]);

	printf("ret= %d\n",ret);

	return 0;
}


