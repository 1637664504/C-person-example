#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>



int main(int argc,char *argv[])
{
	int a,b,ret;
	char opt;
	char buf[1024]={0};
	printf("input:");
	fgets(buf,1024,stdin);
	ret=sscanf(buf,"%d %c %d",&a,&opt,&b);
	printf("ret=%d\n",ret);

}

/*
验证sscanf() 在出错时的返回值。
*/

