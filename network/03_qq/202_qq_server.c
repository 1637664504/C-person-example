#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_LEN 1024

int tcp_listen_init(int port,char *ip)
{
	int fd;
	struct sockaddr_in ser_addr;

	fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd < 0){
		perror("socket fail");
		exit(1);
		
	}
	memset(&ser_addr,0,sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(port);
	ser_addr.sin_addr.s_addr = inet_addr(ip);

	if(bind(fd,(struct sockaddr *)&ser_addr,sizeof(ser_addr)) == -1){
		perror("bind fail");
		exit(1);
	}
	if(listen(fd,10) == -1){
		perror("listen fail");
	}
	printf("bind & listen success\n");

	return fd;
}

int get_accept_fd(int ser_sock)
{
	int fd;
	struct sockaddr_in clnt_addr;
	int len;
	
	len = sizeof(clnt_addr);
	memset(&clnt_addr,0,len);
	fd = accept(ser_sock,(struct sockaddr*)&clnt_addr,&len);
	if(fd < 0){
		perror("accept fail");
		exit(1);
	}
	printf("new tcp connect fd=%d\n",fd);

	return fd;
}

int child_process(int fd)
{
	int len = 0;
	char buf[BUF_LEN]={0};

	close(0);
	len = read(fd,buf,BUF_LEN);
	printf("rcv:%s\n",buf);
	write(fd,buf,len);

	exit(0);
}

int echo_server(int ser_sock)
{
	int fd;
	int pid;
	int count=1;
	while(1){

		fd = get_accept_fd(ser_sock);
		if((pid= fork()) < 0){
			perror("fork fail");
			exit(1);
		}else if(pid == 0){
			child_process(fd);
		}
		printf("new child process: %d\n",count++);
		
	}
	
}

int main(int argc,char *argv[])
{
	int sock;
	int ser_port;
	char *ser_ip;
	

	if(argc !=3){
		printf("usage:%s <port> <port>\n",argv[0]);
		exit(1);
		
	}
	ser_port = atoi(argv[1]);
	ser_ip = argv[2];
	sock = tcp_listen_init(ser_port,ser_ip);
	echo_server(sock);

	return 0;
}


