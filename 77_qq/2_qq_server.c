#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/types.h>


void error_handling(char *message);

int qq_sock_server_init(int port,char * ip)
{
	struct sockaddr_in ser_addr;
	int fd;

	fd =socket(AF_INET,SOCK_STREAM,0);
	if(fd < 0){
		perror("socket fialed!");
		exit(1);
	}

	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(port);
	if(*ip){
		ser_addr.sin_addr.s_addr = inet_addr(ip);
		printf("liuj-- 11111\n");
	}else{
		ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		printf("liuj--2222 \n");
	}

	if(bind(fd,(struct sockaddr*)&ser_addr,sizeof(ser_addr)) < 0){
		perror("bind fialed!");
		exit(1);
	}

	return fd;
}

int get_accept_sock(int fd)
{
	struct sockaddr_in client_addr;
	int clnt_fd;
	int len;
	len = sizeof(client_addr);
	clnt_fd = accept(fd,(struct sockaddr *)&client_addr,&len);
	if(clnt_fd < 0){
		perror("accept fialed!");
		exit(1);
	}

	return clnt_fd;
}

int qq_recv_and_show(int fd)
{
	fd_set r_set;
	struct timeval tm;
	int max=fd+1;
	char buf[1024]={0};
	int ret;
	
	FD_ZERO(&r_set);
	FD_SET(fd,&r_set);
	tm.tv_sec=10;
	tm.tv_usec=0;
	close(0);

loop:
	ret = select(max,&r_set,NULL,NULL,&tm);
	if(ret < 0){
		perror("slect error");
		exit(1);
	}
	else if(ret == 0){
		printf("recv msg timout\n");
		goto loop;
	}else{
		memset(buf,0,1024);
		if(FD_ISSET(fd,&r_set)){
			read(fd,buf,1024);
			printf("\t rcv:%s\n",buf);
		}
		goto loop;
	}
	
}

int qq_main(int listen_fd)
{
	int fd;
	int pid;
	int len;
	fd = get_accept_sock(listen_fd);

	if((pid =fork()) == 0){
		// read
		qq_recv_and_show(fd);
	}

	while(1)
	{
		char buf[1024] = {0};
		len = read(0,buf,1024);
		if(strcpy("quit",buf) == 0){
			printf("now quit qq!");
			return 0;
		}
		write(fd,buf,len);
	}
}

int main(int argc, char *argv[]){

	int ser_fd;
	int port;
	char *ser_addr = NULL;

	if(argc < 2 || argc > 4){
		printf("Usage:%s <port> [ip]\n",argv[0]);
		exit(1);
	}

	port = atoi(argv[1]);
	ser_addr= argv[2];

	ser_fd = qq_sock_server_init(port,ser_addr);
	qq_main(ser_fd);
	return 0;

}

void error_handling(char *message){

	fputs(message,stderr);
	fputs("\n",stderr);
	exit(1);
}
