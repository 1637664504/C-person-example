#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void help(void)
{
	static char *str="Usage: program port [local_ip]\n";
	printf("%s",str);
}

int fd_set_nonblock(int fd)
{
    int ret;
    int flags = fcntl(fd, F_GETFL, 0);
    ret = fcntl(fd, F_SETFL, flags|O_NONBLOCK);

    return ret;
}

int main(int argc, char* argv[])
{
	int port = 5566;
	int ret;
	char server_ip[16]="0.0.0.0";
	if(argc == 2)
	{
		port = atoi(argv[1]);
	}
	else if(argc == 3)
	{
		port = atoi(argv[1]);
		strncpy(server_ip,argv[2],16);
	}
	else{
		help();
	}

	//1.socket
	int listen_fd = socket(AF_INET,SOCK_STREAM,0);
	if(listen_fd == -1)
	{
		perror("socket listen_fd fail");
		return -1;
	}
	//1.1 解决重启进程 bind: Address already in use. TIME_WAIT导致
	int val = 1;
	ret = setsockopt(listen_fd,SOL_SOCKET,SO_REUSEADDR,(void *)&val,sizeof(int));
	if(ret == -1)
	{
		perror("setsockopt re_user_addr fail");
		exit(1);
	}
	//1.2 设置非阻塞
	fd_set_nonblock(listen_fd);


	//2.bind & listen
	struct sockaddr_in serveraddr;
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	inet_aton(server_ip,&(serveraddr.sin_addr));

	ret = bind(listen_fd,(struct sockaddr *)&serveraddr, sizeof(serveraddr));
	if(ret == -1)
	{
		perror("bind fail");
		return -1;
	}
	ret = listen(listen_fd,64);
	if(ret == -1)
	{
		perror("listen fail");
		return -1;
	}

	//3.epoll event
	int epoll_fd;
	epoll_fd = epoll_create(256);
	struct epoll_event ev;
	ev.data.fd = listen_fd;
	ev.events = EPOLLIN;
	epoll_ctl(epoll_fd,EPOLL_CTL_ADD,listen_fd,&ev);

	struct epoll_event events[64];
	int evs_num;
	int i;
	for(;;)
	{
		evs_num = epoll_wait(epoll_fd,events,64,32000);
		for(i=0;i<evs_num;i++)
		{
			if(events[i].data.fd == listen_fd)
			{
				struct sockaddr_in clientaddr = {0};
				socklen_t clilen;
				int connfd = accept(listen_fd,(struct sockaddr *)&clientaddr,&clilen);
				if(connfd == -1)
				{
					//错误原因: EBADF 未打开套接字， EAGAIN 标记为nonblocking
					perror("accept fail");
					return -1;
				}

				char *cli_ip = inet_ntoa(clientaddr.sin_addr);
				printf("new client from %s",cli_ip);
				ev.data.fd = connfd;
				ev.events = EPOLLIN;
				epoll_ctl(epoll_fd,EPOLL_CTL_ADD,connfd,&ev);
			}
			else if(events[i].events&EPOLLIN)
			{
				int ev_fd = events[i].data.fd;
				int len;
				char buf[256];
				if(ev_fd < 0)
					continue;
				if((len = read(ev_fd,buf,sizeof(buf))) < 0)
				{
					if(errno == ECONNRESET)
					{
						close(ev_fd);
						events[i].data.fd = -1;
					}
					else
						perror("read fail");
				}
				else if(len == 0)	//errno = EBADF, len = 0. 即客户端断开。
				{
					close(ev_fd);
					events[i].data.fd = -1;
				}
				else				//成功读取
				{
					printf("recv msg: %s",buf);
				}
			}
		}
	}

	return 0;
}