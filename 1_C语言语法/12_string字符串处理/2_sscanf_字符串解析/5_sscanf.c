#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
	char *str="num=12 a=14";
    int num=0;
    int a=14;
    sscanf(str,"num=%d a=%d",&num,&a);

    printf(" %d %d\n",num,a);
    return 0;
}