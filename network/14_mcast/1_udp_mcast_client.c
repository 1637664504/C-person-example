#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUF_LEN 256
char DEFAULT_IP[64]="224.0.0.88";
int DEFAULT_PORT=6655;

int udp_sock_init(int port,char *ip,struct sockaddr_in *serv_addr)
{
	int sock;

	sock =socket(AF_INET,SOCK_DGRAM,0);
	serv_addr->sin_family = AF_INET;
	serv_addr->sin_port = htons(port);
	serv_addr->sin_addr.s_addr = inet_addr(ip);

	return sock;
}


int main(int argc,char *argv[])
{
	int sock;
	int ser_port;
	char *ser_ip;
	struct sockaddr_in serv_addr,from_addr;
	socklen_t addr_len;
    int time=0, err;
	

	if(argc !=2){
		printf("usage:%s <ip> <port>\n",argv[0]);
        printf("Default address:%s port:%d\n",DEFAULT_IP,DEFAULT_PORT);
		ser_port=DEFAULT_PORT;
		ser_ip=DEFAULT_IP;
		
	}else if(argc==2){
		ser_port = atoi(argv[1]);
	}

	sock = udp_sock_init(ser_port,ser_ip,&serv_addr);
    err = bind(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    if(err < 0){
        perror("bind()");
        return -1;
    }
    int loop =1;
    err = setscokopt(s,IPPROTO_IP,IP_MULTICAST_LOOP,&loop,sizeof(loop));
    if(err < 0){
        perror("setsockopt()");
        return -2;
    }
    
	//do_someting(sock);
	while(time-- < 5){
		char sendbuf[BUF_LEN] = {0};
		char recvbuf[BUF_LEN] = {0};
		int len;
		fputs("IN:",stdout);
		fgets(sendbuf,BUF_LEN,stdin);
		if(!strcmp("quit",sendbuf) || !strcmp("exit",sendbuf)){
			break;
		}
		sendto(sock,sendbuf,strlen(sendbuf),0,(struct sockaddr*)&serv_addr,(sizeof(serv_addr)));
		addr_len = sizeof(from_addr);
		len = recvfrom(sock,recvbuf,BUF_LEN,0,(struct sockaddr*)&from_addr,&addr_len);
		recvbuf[len]=0;
		printf("recv:%s\n",recvbuf);
		
	}

}


