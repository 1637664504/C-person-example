#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main ( int argc, char *argv[] )
{
	char *file = "123.txt";
	if(argc == 2){
		file = argv[1];
	}

	FILE *fp = NULL;
	fp = fopen(file,"r");
	if(!fp)
	{
		perror("fopen error");
		return -1;
	}

	char buf[32];
	int ret,len;
	ret = fread(buf,sizeof(buf),1,fp);
	len = ftell(fp);

	ret = fseek(fp,-32,SEEK_CUR);
	len = ftell(fp);
	ret = fread(buf,sizeof(buf),1,fp);
	printf("%s",buf);

    return 0;
}