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

int udp_bind_init(int port,char *ip,struct sockaddr_in *serv_addr)
{
	int sock;

	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock < 0){
		perror("socket fail");
		exit(1);
	}
	memset(serv_addr,0,sizeof(serv_addr));
	serv_addr->sin_family = AF_INET;
	serv_addr->sin_port = htons(port);
	serv_addr->sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sock,(struct sockaddr *)serv_addr,sizeof(*serv_addr)) == -1){
		perror("bind fail");
		exit(1);
	}

	printf("udp bind  success\n");

	return sock;
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
			//child_process(fd);
		}
		printf("new child process: %d\n",count++);
		
	}
	
}

int main(int argc,char *argv[])
{
	int sock;
	int ser_port;
	char *ser_ip;
	struct sockaddr_in serv_addr,clnt_addr;
	socklen_t addr_len;
	

	if(argc !=2){
		printf("usage:%s <port> <port>\n",argv[0]);
		ser_port=DEFAULT_PORT;
		ser_ip=DEFAULT_IP;
		
	}else if(argc==2){
		ser_port = atoi(argv[1]);
	}

	sock = udp_bind_init(ser_port,ser_ip,&serv_addr);
	//do_main(sock);
	addr_len = sizeof(serv_addr);
	while(1){
		char msg[BUF_LEN] = {0};
		int len;
		len = recvfrom(sock,msg,BUF_LEN,0,(struct sockaddr*)&clnt_addr,&addr_len);
		printf("len=%d,msg:%s\n",len,msg);
		sendto(sock,msg,len,0,(struct sockaddr*)&clnt_addr,addr_len);
	}

	return 0;
}


