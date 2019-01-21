#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
#define pr_debug(format, ...) fprintf (stderr, format, ## __VA_ARGS__)
#else
#define pr_debug(format, ...) do{}while(0)
#endif

#define DEBUG 1
int add(void)
{
	pr_debug("11111");
}
#undef DEBUG

int main ( int argc, char *argv[] )
{
	char buf[16]="1400";
	int n;
	n = atoi(buf);
	pr_debug("222 n=%d\n",n);
	add();

	return 0;
}


