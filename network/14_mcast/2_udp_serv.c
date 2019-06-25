/*
udp echo验证
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_LEN 256
char DEFAULT_IP[64]="224.0.0.88";
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
	serv_addr->sin_addr.s_addr = inet_addr(ip);

//	if(bind(sock,(struct sockaddr *)serv_addr,sizeof(*serv_addr)) == -1){
//		perror("bind fail");
//		exit(1);
//	}

	printf("udp bind  success\n");

	return sock;
}

int main(int argc,char *argv[])
{
	int sock;
	int ser_port;
	char *ser_ip;
	struct sockaddr_in serv_addr,clnt_addr;
	socklen_t addr_len;
    int buf_len;
    char msg[BUF_LEN]="Hi, welcome mcast __liujiang";

	if(argc !=2){
		printf("usage:%s <port> <port>\n",argv[0]);
        printf("Default address:%s port:%d\n",DEFAULT_IP,DEFAULT_PORT);
		ser_port=DEFAULT_PORT;
		ser_ip=DEFAULT_IP;
		
	}else if(argc==2){
		ser_port = atoi(argv[1]);
	}

	sock = udp_bind_init(ser_port,ser_ip,&serv_addr);
	addr_len = sizeof(serv_addr);
    buf_len = strlen(msg);
	while(1){
        int len;
		//len = recvfrom(sock,msg,BUF_LEN,0,(struct sockaddr*)&clnt_addr,&addr_len);
		//printf("len=%d,msg:%s\n",len,msg);
		len = sendto(sock,msg,buf_len,0,(struct sockaddr*)&serv_addr,addr_len);
        if(len < 0){
            perror("sendto() error");
            return -2;
        }
        sleep(1);
	}

	return 0;
}


