#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>



int main(int argc,char *argv[])
{
	int a,b;
	char opt;
	printf("input:");
	scanf("%d %c %d",&a,&opt,&b);
	printf("%d %c %d",a,opt,b);

}


