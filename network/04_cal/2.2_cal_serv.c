/*
验证多个计算器 客户端登录情况
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
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);

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

int do_cal(char opt,int a,int b)
{
	int ret;
	switch (opt){
	case '+':
		ret=a+b; break;
	case '-':
		ret=a-b; break;
	case '*':
		ret=a*b; break;
	case '/':
		ret=a/b; break;
	default:
		ret = '?'; break;
	}

	return ret;
}

int do_someting(int sock)
{
	char recvbuf[1024] = {0};
	char sendbuf[1024] = {0};
	int a,b,ret,len;
	char opt;

	while((len = read(sock,recvbuf,BUF_LEN)) > 0){
		ret = sscanf(recvbuf,"%d %c %d",&a,&opt,&b);
		if(ret < 3){
			write(sock,"error",5);
			return -1;
		}
		//printf("a=%d opt=%c b=%d\n",a,opt,b);
		ret = do_cal(opt,a,b);
		memset(sendbuf,0,BUF_LEN);
		len=sprintf(sendbuf,"%d",ret);
		write(sock,sendbuf,len);
	}
	printf("END--------\n");

	return len;
}

int child_process(int fd)
{
	int len = 0;
	char buf[BUF_LEN]={0};

	do_someting(fd);

	exit(0);
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
			child_process(fd);
		}
		printf("new child process: %d\n",count++);
		
	}
	
}

int main(int argc,char *argv[])
{
	int sock;
	int ser_port;
	char *ser_ip;
	

	if(argc !=3){
		printf("usage:%s <port> <port>\n",argv[0]);
		ser_port=DEFAULT_PORT;
		ser_ip=DEFAULT_IP;
		
	}else if(argc==3){
		ser_port = atoi(argv[1]);
		ser_ip = argv[2];
	}

	sock = tcp_listen_init(ser_port,ser_ip);
	do_main(sock);

	return 0;
}


