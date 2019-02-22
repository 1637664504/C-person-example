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

int udp_sock_init(int port,char *ip,struct sockaddr_in *serv_addr)
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
	serv_addr->sin_addr.s_addr = inet_addr(ip);

	return sock;
}

int do_main(int sock,struct sockaddr_in addr)
{
	int len;
	struct sockaddr_in clnt_addr;
	socklen_t addr_len;

	while(1){
		char sendbuf[BUF_LEN]={0};
		char recvbuf[BUF_LEN]={0};
		fputs("in:",stdout);
		fgets(sendbuf,BUF_LEN,stdin);
		if(!strcmp("exit",sendbuf)){
			return 0;
		}
		sendto(sock,sendbuf,strlen(sendbuf),0,(struct sockaddr*)&addr,sizeof(addr));
		len = recvfrom(sock,recvbuf,BUF_LEN,0,(struct sockaddr*)&clnt_addr,&addr_len);
		recvbuf[len]=0;
		printf("recv:%s",recvbuf);
	}

	return 0;
}

#define MSGLEN 512
int read_msg_port = 7755;
char read_msg_ip[16] = "127.0.0.1";
int do_read_msg()
{
	int sock;
	int len;
	socklen_t addr_len;
	struct sockaddr_in serv_addr,clnt_addr;
	sock = udp_sock_bind_init(read_msg_port,read_msg_ip,&serv_addr);
	close(0);
	shutdown(sock,SHUT_WR);
	while(1){
		char msg[MSGLEN]={0};
		len = recvfrom(sock,msg,MSGLEN,0,(struct sockaddr*)&clnt_addr,&addr_len);
		if(len==0 || !strcmp("_exit_",msg)){
			printf("peer connect termined. Exit\n");
			return 0;
		}
		printf("\nrecv--:%s\n",msg);
	}
	close(sock);
	return 0;
}

int send_msg_port = 7766;
char send_msg_ip[16] = "127.0.0.1";
int do_send_msg()
{
	int sock;	//send_msg
	int len;
	socklen_t addr_len;
	struct sockaddr_in serv_addr,clnt_addr;
	sock = udp_sock_init(send_msg_port,send_msg_ip,&serv_addr);
	close(1);
	shutdown(sock,SHUT_RD);
	while(1){
		char sendbuf[BUF_LEN]={0};
		fputs("in:",stderr);
		fgets(sendbuf,BUF_LEN,stdin);
		if(!strcmp("exit",sendbuf)){
			break;
		}
		sendto(sock,sendbuf,strlen(sendbuf),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	}
	sendto(sock,"_exit_",6,0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	close(sock);
	return 0;
}

int main(int argc,char *argv[])
{
	int sock;
	int ser_port;
	char *ser_ip;
	struct sockaddr_in serv_addr;
	int pid;

	if(argc !=2){
		printf("usage:%s <port> <port>.Set default port:6655 ip:127.0.0.1\n",argv[0]);
		ser_port=DEFAULT_PORT;
		ser_ip=DEFAULT_IP;
		
	}else if(argc==2){
		ser_port = atoi(argv[1]);
	}

	//sock = udp_sock_init(ser_port,ser_ip,&serv_addr);
	//do_main(sock,serv_addr);
	pid = fork();
	if(pid == 0){
		do_read_msg();
	}else{
		do_send_msg();
	}

	return 0;
}


