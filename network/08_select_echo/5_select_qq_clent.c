#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define DEBUG
#ifdef DEBUG
#define debug printf
#else
#define debug
#endif

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
		recvbuf[len]=0;
		printf("recv:%s",recvbuf);
	}

}

int qq_client(int sock)
{
	fd_set reads,tmps;
	int ret,maxfd,i,len;
	struct timeval tv;
	FD_ZERO(&reads);
	FD_SET(STDIN_FILENO,&reads);
	FD_SET(sock,&reads);
	maxfd=sock;

	while(1){
		tmps = reads;	//1.必要，不使用tmps，select()会一直超时。原因不知
		tv.tv_sec=5;	//2.必要，ts若不每次初始化，tv_sec貌似会被改变。原因不知
		tv.tv_usec=0;

		ret = select(maxfd+1,&tmps,NULL,NULL,&tv);
		if(ret == -1){
			perror("select fail");
			return 0;
		}else if(ret == 0){
			debug("select timeout\n");
			continue;
		}
		for(i=0;i<maxfd+1;i++){
			if(!FD_ISSET(i,&tmps)){
				continue;
			}
			if(i == sock){
				char recvbuf[BUF_LEN]={0};
				len = read(sock,recvbuf,BUF_LEN);
				if(len == 0){
					printf("serv connected termined;Exit\n");
					return -1;
				}
				//recvbuf[len]=0;
				printf("recv:%s",recvbuf);
			}
			if(i == STDIN_FILENO){
				char msg[BUF_LEN]={0};
				len = read(i,msg,BUF_LEN);
				write(sock,msg,len);

				msg[len-1] = 0;
				printf("--send:%s \n",msg);
			}

		}

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

	sock = tcp_connect(serv_port,serv_ip);
	qq_client(sock);

}

