/*
将标准输出导出到 fd.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUF_LEN 1024

int main(int argc,char *argv[])
{
	int fd;
	fd = open("123.txt",O_RDWR|O_CREAT,0664);
	if(fd < 0){
		perror("open fail");
		exit(1);
	}
	int pid;
	pid = fork();
	if(pid==0){
		printf("child process\n");
		dup2(fd,1);
		system("ls");
		exit(1);
	}
	printf("father process\n");
	return 0;
}



