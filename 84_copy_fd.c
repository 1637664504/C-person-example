#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include <stdlib.h>    
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_LEN 1024

int copy_file(int new,int old)
{
	int len;
	char buf[BUF_LEN]={0};
	while((len=read(old,buf,BUF_LEN)) > 0){
		write(new,buf,len);
	}
	return 0;
}
int main(void)
{
	int new,old;
	old = open("123.txt",O_RDONLY,0664);
	new = open("234.txt",O_RDWR|O_CREAT,0664);
	copy_file(new,old);

	return 0;
}

