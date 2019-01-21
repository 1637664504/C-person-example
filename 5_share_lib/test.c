
#include	<stdlib.h>
#include    <stdio.h>

#include "fun.h"
int main ( int argc, char *argv[] )
{
    int a=10,b=20;
    int c;

    c=add(a,b);
    printf("a+b=%d\n",c);
	c=del(a,b);
	printf("a-b=%d\n",c);
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
