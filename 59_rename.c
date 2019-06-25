#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
	char new[]="1.c";
	char old[]="3.c";
	rename(new,old);
	return 0;
}

