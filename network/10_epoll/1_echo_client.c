#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_LEN 512
char DEFAULT_IP[64]="127.0.0.1";
int DEFAULT_PORT=6655;

int tcp_connect(int port,char *ip)
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

	if(connect(fd,(struct sockaddr *)&ser_addr,sizeof(ser_addr)) == -1){
		perror("connect fail");
		exit(1);
	}
	printf("connect success\n");

	return fd;
}

int echo_client(int sock)
{
	int len;

	while(1){
		char sendbuf[BUF_LEN]={0};
		char recvbuf[BUF_LEN]={0};
		fputs("in:",stdout);
		fgets(sendbuf,BUF_LEN,stdin);
		if(!strncmp("exit",sendbuf,4)){
			close(sock);
			return 0;
		}

		write(sock,sendbuf,strlen(sendbuf));
		len = read(sock,recvbuf,BUF_LEN);
		if(len == 0){
			printf("server connect termined\n");
			close(sock);
			return -1;
		}
		recvbuf[len]=0;
		printf("recv:%s",recvbuf);
	}

	return 0;
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

	sock = tcp_connect(serv_port,serv_ip);
	echo_client(sock);

}

