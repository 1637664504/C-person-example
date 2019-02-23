#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define debug printf
#define EPOLL_SIZE 128
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

int epoll_add(int fd,int opt,int epoll_fds)
{
	struct epoll_event eve;

	eve.events = opt;
	eve.data.fd = fd;
	epoll_ctl(epoll_fds,EPOLL_CTL_ADD,fd,&eve);

	return 0;
}

int do_main(int sock)
{
	int epollfds,fd;
	int ret,len,i;
	struct epoll_event *ep_eves,eve;

	epollfds = epoll_create(EPOLL_SIZE);
	ep_eves = malloc(sizeof(struct epoll_event)*EPOLL_SIZE);
	epoll_add(sock,EPOLLIN,epollfds);
	epoll_add(0,EPOLLIN,epollfds);

	while(1){
		ret =epoll_wait(epollfds,ep_eves,EPOLL_SIZE,-1);
		if(ret == -1){
			perror("epoll error");
			break;
		}
		for(i=0;i<ret;i++){
			fd = ep_eves[i].data.fd;
			if(fd == 0){
				char sendbuf[BUF_LEN]={0};
				fgets(sendbuf,BUF_LEN,stdin);
				if(!strncmp("exit",sendbuf,4)){
					close(sock);
					return -1;
				}
				write(sock,sendbuf,strlen(sendbuf));
			}
			else if(fd == sock){
				char recvbuf[BUF_LEN]={0};
				len = read(sock,recvbuf,BUF_LEN);
				if(len == 0){
					printf("server connect termined\n");
					close(sock);
					return -1;
				}
				recvbuf[len]=0;
				printf("recv:%s",recvbuf);
			}
			else{
				debug("unkonw fd!!\n");
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

	sock = tcp_connect(serv_port,serv_ip);
	do_main(sock);

}

