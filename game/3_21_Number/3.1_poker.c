#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>


#define PLAYER_1 1
#define PLAYER_2 2
#define POKER_NUM 52

int poker[POKER_NUM][2];
void display_user(int (*use)[2],int len)
{
	int i;
	for(i=0;i<len;i++)
		printf("%d:%d ",use[i][0],use[i][1]);

	printf("\n");
}





void send_user_poker(int (*use_1)[2],int (*use_2)[2],int (*use_3)[2],int len)
{
	int i;
	
	for(i=0;i<52,--len>=0;i+=3){
		use_1[len][0] = poker[i][0];
		use_1[len][1] = poker[i][1];
		
		use_2[len][1] = poker[i+=1][0];
		use_2[len][1] = poker[i+=1][1];
		
		use_3[len][1] = poker[i+=2][0];
		use_3[len][1] = poker[i+=2][1];
	}
}

int init_poker()
{
    char suit[4] = {1,2,3,4};
    char rank[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
    int num = 0,a = 0,b = 0,count=0;
    int temp[4][13] = {0};
    srand((unsigned)time(0));

	while(count < 52){
		a = rand()%4;
		b = rand()%13;
		if(temp[a][b]==0){
			poker[count][0]=a;
			poker[count][1]=b;
			printf("%d:%d\n",a,b);
			count++;
			temp[a][b]=1;
		}
	}
    return 0;
}



int do_main(int sock)
{
	struct sockaddr_in clnt_addr;
	socklen_t addr_len;
	int epollfds,clnt_fd;
	int len,ret,i;
	struct epoll_event *epoll_events,event;

	epollfds = epoll_create(EPOLL_SIZE);
	epoll_events = malloc(sizeof(struct epoll_event)*EPOLL_SIZE);
	event.events = EPOLLIN;
	event.data.fd = sock;
	epoll_ctl(epollfds,EPOLL_CTL_ADD,sock,&event);

	while(1){
		ret = epoll_wait(epollfds,epoll_events,EPOLL_SIZE,-1);
		if(ret == -1){
			perror("epoll error");
			break;
		}

		for(i=0;i<ret;i++){
			if(epoll_events[i].data.fd == sock){
				clnt_fd  = get_accept_fd(sock);
				event.events = EPOLLIN;
				event.data.fd = clnt_fd;
				epoll_ctl(epollfds,EPOLL_CTL_ADD,clnt_fd,&event);
				debug("Add epoll to epollfds\n");
			}else{
				char msg[BUF_LEN]={0};
				clnt_fd = epoll_events[i].data.fd;
				
				len = read(clnt_fd,msg,BUF_LEN);
				if(len == 0){
					epoll_ctl(epollfds,EPOLL_CTL_DEL,clnt_fd,NULL);
					close(clnt_fd);
					printf("close client %d\n",clnt_fd);
				}else{
					write(clnt_fd,msg,len);
				}
			}
		}

	}

	return 0;
}


int main(void)
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

