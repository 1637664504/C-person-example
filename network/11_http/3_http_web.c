/*
多进程web版本。
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
    local.sin_port = htons(8000); // 指定固定端口

    int ret = bind(sock,(struct sockaddr *)&local,sizeof(local));
    if( ret < 0 ) 
    {   
    	perror("bind fail");
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
        const char *echo_str = "HTTP/1.0 200 ok\n\\n";
        write(sock,echo_str,strlen(echo_str));
        send_file(sock,file);
    }
    close(sock);
}

pthread_mutex_t mutex;
sem_t sem;
int count=0;

void* pthread_waitpid(void *arg)
{
	int stat;
	while(1){
		wait(&stat);
		count--;
		sem_post(&sem);
	}
}
int do_main(int sock)
{
	int clnt_fd;
	pid_t pid;
	pthread_t pth_id;
	pthread_create(&pth_id,NULL,pthread_waitpid,NULL);
	pthread_detach(pth_id);

	while(1){
		clnt_fd = get_accept_fd(sock);

		pid = fork();
		if(count++ > 10){
			sem_wait(&sem);
		}
		if(pid==-1){
			perror("fork error");
			printf("count=%d\n",count);
			return -1;
		}
		else if(pid == 0){
			handler_request(clnt_fd);
			exit(0);
		}
		close(clnt_fd);
	}
}

int main()
{
	pthread_t thread_id[PTHREAD_MAX];
	int i,*ret;
    int listen_sock = startup();
    sem_init(&sem,0,0);
    do_main(listen_sock);

    
    return 0; 
}
/*
result 1:
webbench -c 2 -t 10 http://127.0.0.1:8000/
Benchmarking: GET http://127.0.0.1:8000/
2 clients, running 10 sec.

Exit!!

./a.out
fork error: Resource temporarily unavailable
count=3603

linux限制user 进程数3603个

result 2:
Add:限制进程数50, 当检查进程数>50时
	有一个线程 wait(),

webbench -c 10 -t 10 http://127.0.0.1:8000/

Speed=354630 pages/min, 1855897 bytes/sec.
Requests: 59105 susceed, 0 failed.

次数 35.4w
*/


