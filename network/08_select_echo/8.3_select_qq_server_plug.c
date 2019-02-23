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

#define CLIENT_MAX 10
struct client_data{
	int id;
	char name[32];
	int c_sock;
} qq_data[CLIENT_MAX];

char not_login[32]="Your frient no login";

#define BUF_LEN 512
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

int get_clientdata_by_name(struct client_data *data,int id,char *name)
{
	int i;
	struct client_data *p = data;

	for(i=0; i<CLIENT_MAX; i++){
		if(p->id == 0)
			continue;

		if(!strncmp(p->name,name,strlen(name))){
			return i;
		}

		p+=1;
	}

	//debug("no find name %s in login database!!\n",name);
	return -1;
}

int get_empty_clientdata(struct client_data *data)
{
	int i;
	struct client_data *p = data;

	for(i=0; i<CLIENT_MAX; i++){
		if(p->id == 0)
			return i;
		p+=1;
	}

	printf("Error Can't add new client\n");
	return -1;
}

int init_clientdata(struct client_data *data,int i)
{

	struct client_data *p = data;

	if(i<0 && i>CLIENT_MAX){
		printf("No this client_data. Over MAX!!\n");
		return -1;
	}
		
	p += i;
	memset(p,0,sizeof(struct client_data));

	return 0;
}


int set_client_data(int id,char *name,int sock,struct client_data *data)
{
	int i;
	struct client_data *p=data;
	if((i=get_empty_clientdata(data)) == -1){
		return -1;
	}
	
	p+=i;
	//memset(p,0,sizeof(struct client_data));
	p->id = id;
	strcpy(&p->name[0],name);
	p->c_sock = sock;

	return 0;
}

int verify_id_and_name(int sock,struct client_data *data)
{
	char msg[BUF_LEN]={0};
	char client_name[32]={0};
	int len,client_id;

	len = read(sock,msg,BUF_LEN);
	if(len == 0)
		return -1;
	sscanf(msg,"_id:%d _name:%s",&client_id,client_name);
	//debug("client_id=%d,client_name=%s\n",client_id,client_name);
	if(client_id && client_name){
		return set_client_data(client_id,client_name,sock,data);
	}

	return -1;
}

int do_qq_server(int sock)
{
	fd_set reads,tmp_fds;
	struct timeval tv;
	int ret,i,len;
	int maxfd,clnt_sock;

	FD_ZERO(&reads);
	FD_SET(sock,&reads);
	//FD_SET(STDIN_FILENO,&reads);
	maxfd = sock;

	while(1){
		tmp_fds = reads;
		tv.tv_sec = 5;
		tv.tv_usec = 0;

		ret = select(maxfd+1,&tmp_fds,NULL,NULL,&tv);
		if(ret == -1){
			perror("select fail");
			return 0;
		}else if(ret == 0){
			//debug("select timeout\n");
			continue;
		}

		for(i=0;i<maxfd+1;i++){
			if(!FD_ISSET(i,&tmp_fds)){
				continue;
			}

			if(i == sock){		//new tcp client connect
				clnt_sock = get_accept_fd(sock);
				if(verify_id_and_name(clnt_sock,qq_data)){
					continue;
				}
				FD_SET(clnt_sock,&reads);
				if(maxfd < clnt_sock){
					maxfd = clnt_sock;
				}

			}
			#if 0
			else if(i == STDIN_FILENO){
				
				char msg[BUF_LEN]={0};
				len = read(0,msg,BUF_LEN);
				msg[len-1] = 0;
				printf("--send:%s \n",msg);

				write(clnt_sock,msg,len);
				
			}
			#endif
			else{
				char recvbuf[BUF_LEN]={0},sendbuf[BUF_LEN]={0};
				char recv_name[32]={0};
				int idx;

				len = read(i,recvbuf,BUF_LEN);
				if(len == 0){
					FD_CLR(i,&reads);
					close(i);
					debug("client connect termined;Exit\n");
				}else{
					sscanf(recvbuf,"%*[^@]@%[^:]",recv_name);
					debug("recv_name=%s\n",recv_name);
					if((idx=get_clientdata_by_name(qq_data,0,recv_name)) == -1){
						len = sprintf(sendbuf,"Your frient: %s no login !!",recv_name);
						write(i,sendbuf,len);
					}else{
						write(qq_data[idx].c_sock,recvbuf,len);
					}
				}
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

	memset(qq_data,0,sizeof(struct client_data)*32);
	sock = tcp_listen_init(serv_port,serv_ip);
	do_qq_server(sock);

	return 0;
}



