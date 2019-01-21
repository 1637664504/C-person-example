
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAXNAMELEN 256
int main ( int argc, char *argv[] )
{
	char *var,*value;
	char hostname[MAXNAMELEN]={0};
    gethostname(hostname, MAXNAMELEN);

	printf ( "%s\n",hostname);
	return 0;
}
