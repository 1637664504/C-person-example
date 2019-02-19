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
		printf("send:\t");
		len = read(1,buf,BUF_LEN);
		write(sock,buf,len);
		printf("recv:%s\n",buf);
	//}
}

int fd[2];
int qq_recv(int sock)
{
	int len;
	close(0);
	//close(1);
	close(fd[0]);
	close(fd[1]);

	while(1){
		char buf[BUF_LEN]={0};
		len = read(sock,buf,BUF_LEN);
		if(len <= 0){
			printf("tcp disconnect. exit\n");
			break;
		}
		if(!strcmp("quit",buf)){
			printf("server send disconnect.\n");
			break;
		}
		//write(fd[1],buf,len);
		printf("recv:%s\n",buf);
	}

	exit(0);
}

int qq_send(int sock)
{
	int len;
	close(fd[0]);
	close(fd[1]);
	while(1){
		char buf[BUF_LEN]={0};
		len = read(1,buf,BUF_LEN);
		if(!strcmp("quit",buf)){
			printf("client quit.\n");
			break;
		}

		write(sock,buf,len);
	}
}

int qq_client(int sock)
{
	int pid;
	if(pipe(fd)){
		perror("pipe() fail");
		exit(1);
	}
	if((pid = fork())<0){
		perror("fork fail");
		exit(1);
	}else if(pid == 0){
		//child process
		qq_recv(sock);
	}else{
		//father process
		qq_send(sock);
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
	sock = tcp_connect(ser_port,ser_ip);
	echo_client(sock);

}

