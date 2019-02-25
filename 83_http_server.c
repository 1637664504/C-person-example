/*
实现简易http web,
不涉及http协议。
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
#define BUF_LEN 1024

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

	memset(file,0,512);
	strcpy(file,"index.html");
	fd = open(file,O_RDONLY);
	copy_file(sock,fd);
}

void* handler_request(void * arg)
{
    int sock = *((int*)arg);
    char buf[4896];
    char file[512];
    ssize_t s = read(sock,buf,sizeof(buf)-1);
    if( s > 0 )
    {
        buf[s] = 0;
        printf(" %s ",buf);
        //const char *echo_str = "HTTP/1.0 200 ok\n\n<html><h1>Welcome to my http server!</h1><html>\n";
        const char *echo_str = "HTTP/1.0 200 ok\n\\n";
        write(sock,echo_str,strlen(echo_str));
        send_file(sock,file);
    }
    close(sock);
}

int main()
{
    int listen_sock = startup();
    while(1)
    {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int sock = accept(listen_sock,(struct sockaddr*)&client,&len);
        if(sock < 0)
        {
            continue;
        }
        pthread_t tid;
        pthread_create(&tid,NULL,handler_request,(void *)&sock);
               pthread_detach(tid);
    }
    return 0; 
}

