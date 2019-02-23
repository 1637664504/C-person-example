#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define debug printf
#define BUF_LEN 512
#define EPOLL_SIZE 128
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

int child_process(int fd)
{
	int len = 0;
	char buf[BUF_LEN]={0};

	close(0);
	len = read(fd,buf,BUF_LEN);
	printf("rcv:%s\n",buf);
	write(fd,buf,len);

	exit(0);
}

int echo_server(int sock)
{
	int epollfds,clnt_fd;
	int ret,len,i;
	struct epoll_event *ep_eves,eve;

	epollfds = epoll_create(EPOLL_SIZE);
	ep_eves = malloc(sizeof(struct epoll_event)*EPOLL_SIZE);
	eve.events = EPOLLIN;
	eve.data.fd = sock;
	epoll_ctl(epollfds,EPOLL_CTL_ADD,sock,&eve);

	while(1){
		ret = epoll_wait(epollfds,ep_eves,EPOLL_SIZE,-1);
		if(ret==-1){
			perror("epoll_wait error");
			break;
		}
		for(i=0;i<ret;i++){
			if(ep_eves[i].data.fd == sock){
				clnt_fd = get_accept_fd(sock);
				eve.events = EPOLLIN;
				eve.data.fd = clnt_fd;
				epoll_ctl(epollfds,EPOLL_CTL_ADD,clnt_fd,&eve);
			}else{
				char msg[BUF_LEN]={0};
				clnt_fd = ep_eves[i].data.fd;
				len = read(clnt_fd,msg,BUF_LEN);
				if(len == 0){
					epoll_ctl(epollfds,EPOLL_CTL_DEL,clnt_fd,NULL);
					close(clnt_fd);
					debug("client connect termin %d\n",clnt_fd);
				}else{
					write(clnt_fd,msg,len);
				}
				
			}
		}

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

	sock = tcp_listen_init(serv_port,serv_ip);
	echo_server(sock);

	return 0;
}


