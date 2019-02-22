#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_LEN 512
char DEFAULT_IP[64]="127.0.0.1";
int DEFAULT_PORT=6655;

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

int echo_server(int fd)
{
	int len = 0;

	while(1){
		char buf[BUF_LEN]={0};
		len = read(fd,buf,BUF_LEN);
		if(len == 0){
			printf("client connet termined\n");
			break;
		}
		printf("rcv:%s\n",buf);
		write(fd,buf,len);
	}

	return 0;
}

int do_main(int ser_sock)
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
			echo_server(fd);
		}
		printf("new child process:pid=%d %d\n",pid,count++);
	}
	
}

int main(int argc,char *argv[])
{
	int sock;
	int serv_port;
	char *serv_ip;
	

	printf("usage:%s <port> <ip>.Set default port:6655 ip:127.0.0.1\n",argv[0]);
	if(argc == 1){
		serv_port = DEFAULT_PORT;
		serv_ip = DEFAULT_IP;
	}else if(argc == 2){
		serv_port = atoi(argv[1]);
		serv_ip = DEFAULT_IP;
	}else if(argc == 3){
		serv_port = atoi(argv[1]);
		serv_ip = argv[2];
	}else{
		printf("don't support other option\n");
		exit(0);
	}

	sock = tcp_listen_init(serv_port,serv_ip);
	do_main(sock);

	return 0;
}


