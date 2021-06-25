#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
extern int add(int a,int b);
void a()
{
	printf("%s\n",__func__);
}

int b()
{
	printf("%s",__func__);

	return 0;
}

int main(int argc,char *argv[])
{
	sleep(1);
	a();
	b();
	int a=2,b=3;
	int c=add(a,b);
}


