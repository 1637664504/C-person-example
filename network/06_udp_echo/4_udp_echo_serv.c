/*
udp echo验证
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_LEN 1024
char DEFAULT_IP[64]="127.0.0.1";
int DEFAULT_PORT=6655;

int udp_sock_bind_init(int port,char *ip,struct sockaddr_in *serv_addr)
{
	int sock;

	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock < 0){
		perror("socket udp fail");
		exit(-1);
	}
	memset(serv_addr,0,sizeof(*serv_addr));
	serv_addr->sin_family = AF_INET;
	serv_addr->sin_port = htons(port);
	serv_addr->sin_addr.s_addr = htonl(INADDR_ANY);
	if((bind(sock,(struct sockaddr*)serv_addr,sizeof(*serv_addr))) < 0){
		perror("bind udp error");
		exit(-1);
	}

	return sock;
}

int do_main(int sock,struct sockaddr_in s_addr)
{
	struct sockaddr_in c_addr;
	socklen_t addr_len;
	int len;
	while(1){
		char msg[BUF_LEN]={0};
		len=recvfrom(sock,msg,BUF_LEN,0,(struct sockaddr*)&c_addr,&addr_len);
		printf("recv:%s\n",msg);
		sendto(sock,msg,len,0,(struct sockaddr*)&c_addr,sizeof(c_addr));
	}
}

int main(int argc,char *argv[])
{
	int sock;
	int ser_port;
	char *ser_ip;
	struct sockaddr_in serv_addr;

	if(argc !=2){
		printf("usage:%s <port> <port>\n",argv[0]);
		ser_port=DEFAULT_PORT;
		ser_ip=DEFAULT_IP;
		
	}else if(argc==2){
		ser_port = atoi(argv[1]);
	}

	sock = udp_sock_bind_init(ser_port,ser_ip,&serv_addr);
	do_main(sock,serv_addr);

	return 0;
}


