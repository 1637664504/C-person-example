#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main ( int argc, char *argv[] )
{
	char *p;
	p = getlogin();
	printf("%s\n",p);

	return EXIT_SUCCESS;
}

