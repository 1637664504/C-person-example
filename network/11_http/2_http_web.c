/*
多线程版本http web,
1.预先创建PTHREAD_MAX 个线程
2.lock
3.client_fd = accept()
3.unlock
4.线程 后半部继续处理http请求。
*/
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <semaphore.h>

#define BUF_LEN 1024
#define PTHREAD_MAX 32
#define EPOLL_SIZE 70

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

	return fd;
}


int startup()
{
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0)
    {   
        exit(1);//退出进程
    }   

    int opt = 1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(8080); // 指定固定端口

    int ret = bind(sock,(struct sockaddr *)&local,sizeof(local));
    if( ret < 0 ) 
    {   
        exit(2);
    }   

    if( listen(sock,5) < 0 ) 
    {   
        exit(3);
    }   
        return sock;
}


int copy_file(int new,int old)
{
	int len;
	char buf[BUF_LEN] = {0};
	while((len=read(old,buf,BUF_LEN)) > 0){
		write(new,buf,len);
	}
	return 0;
}

int send_file(int sock,char *file)
{
	int fd,len;

	strcpy(file,"index.html");
	fd = open(file,O_RDONLY);
	copy_file(sock,fd);
}

void* handler_request(int sock)
{
    char buf[4896];
    char file[512]={0};
    ssize_t s = read(sock,buf,sizeof(buf)-1);
    if( s > 0 )
    {
        buf[s] = 0;
        //printf(" %s ",buf);
        //const char *echo_str = "HTTP/1.0 200 ok\n\n<html><h1>Welcome to my http server!</h1><html>\n";
        const char *echo_str = "HTTP/1.0 200 ok\n\\n";
        write(sock,echo_str,strlen(echo_str));
        send_file(sock,file);
    }
}

pthread_mutex_t mutex;
sem_t sem;

void *pthread_func(void *arg)
{
	int sock=*(int *)arg;
	int clnt_fd;

	while(1){
		pthread_mutex_lock(&mutex);
		clnt_fd = get_accept_fd(sock);
		pthread_mutex_unlock(&mutex);
		handler_request(clnt_fd);
		close(clnt_fd);
		
	}
}

int main()
{
	pthread_t thread_id[PTHREAD_MAX];
	int i,*ret;
    int listen_sock = startup();
    
    pthread_mutex_init(&mutex,NULL);
    for(i=0;i<PTHREAD_MAX;i++){
		pthread_create(&thread_id[i],NULL,pthread_func,(void *)&listen_sock);
		pthread_join(thread_id[i],NULL);
    }
    
    return 0; 
}

/*
 webbench -c 10 -t 10 http://127.0.0.1:8080/

Speed=1452366 pages/min, 465870 bytes/sec.
Requests: 242061 susceed, 0 failed.

次数 145.2w
*/
