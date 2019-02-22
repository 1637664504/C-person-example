#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_LEN 1024
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

void do_someting(int sock)
{
	char sendbuf[BUF_LEN] = {0};
	char recvbuf[BUF_LEN] = {0};
	int len;
	int result;

	while(1){
		printf("input:");
		fgets(sendbuf,BUF_LEN,stdin);
		if(!strcmp("quit",sendbuf) || !strcmp("exit",sendbuf)){
			break;
		}

		write(sock,sendbuf,strlen(sendbuf));
		read(sock,recvbuf,BUF_LEN);
		if(!strncmp("error",recvbuf,5)){
			printf("cal result error;Check input\n");
			printf("buf=%s\n",recvbuf);
		}
		printf("result: %s\n",recvbuf);
	}
}

int main(int argc,char *argv[])
{
	int sock;
	int ser_port;
	char *ser_ip;
	

	if(argc !=3){
		printf("usage:%s <port> <port>.Set default port:6655 ip:127.0.0.1\n",argv[0]);
		ser_port=DEFAULT_PORT;
		ser_ip=DEFAULT_IP;
		
	}else if(argc==3){
		ser_port = atoi(argv[1]);
		ser_ip = argv[2];
	}

	sock = tcp_connect(ser_port,ser_ip);
	do_someting(sock);

}


