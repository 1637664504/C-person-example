#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_LEN 1024

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
	//char msg[32]={0};
	//read(sock,msg,32);
	//printf("rcv from server: %s\n",msg);
	//while(1){
		int len;
		char buf[1024];
		printf("send:");
		len = read(1,buf,BUF_LEN);
		write(sock,buf,len);
		printf("recv:%s\n",buf);
	//}
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
	sock = tcp_connect(ser_port,ser_ip);
	echo_client(sock);

}

