#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SVN_ID
int main ( int argc, char *argv[] )
{
	char filename[64]="liujiang123zbc";
	char *p;
	p=strstr(filename,"123");
    printf("p=%s\n",p);
	
	
	return 0;
}



