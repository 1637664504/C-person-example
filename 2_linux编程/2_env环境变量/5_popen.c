#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int getCmdResult(const char *cmd, char *result, int len)
{
    int ret = 0;
    FILE *fp = popen(cmd, "r");

	if(!fp) 
		return 0;
    ret = fread(result,len,1,fp);
    pclose(fp);

    return ret;
}

int main ( int argc, char *argv[] )
{
    char buf[256] = {0};
    getCmdResult("ls",buf,sizeof(buf)-1);
    printf("buf=%s\n",buf);
    return 0;
}