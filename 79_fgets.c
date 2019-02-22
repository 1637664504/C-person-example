#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>



int main(int argc,char *argv[])
{
	char buf[1024]={0};
	fgets(buf,1024,stdin);
	printf("%s 11\n",buf);
	
	return 0;
}


