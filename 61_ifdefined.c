#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SVN_ID
int main ( int argc, char *argv[] )
{
	char filename[64]="js/lang/tr/translate.json?123?abc";
	char *p;
	if(strstr(filename,"translate.json")){
		printf("liuj-- 1111111\n");
		p=strchr(filename,'?');
		printf("liuj-- p=%s\n",p);
		*p='\0';
		printf("liuj-- file=%s\n",filename);
	}
	
	return 0;
}



