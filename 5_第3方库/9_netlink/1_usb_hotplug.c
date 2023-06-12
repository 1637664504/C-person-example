#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include<linux/netlink.h>
#define UEVENT_BUFFER_SIZE 2048
int main()
{
    struct sockaddr_nl client;
    struct timeval tv;
    int sock,rcvlen,ret;
    fd_set fds;
    int buffsize=1024;
    sock = socket(AF_NETLINK,SOCK_RAW,NETLINK_KOBJECT_UEVENT);
    memset(&client,0,sizeof(client));
    client.nl_family = AF_NETLINK;
    client.nl_pid=getpid();
    client.nl_groups = 1;
    setsockopt(sock,SOL_SOCKET,SO_RCVBUF,&buffsize,sizeof(buffsize));
    bind(sock,(struct sockaddr*)&client,sizeof(client));

    while(1){
        char buf[UEVENT_BUFFER_SIZE] = {0};
        FD_ZERO(&fds);
        FD_SET(sock,&fds);
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        ret = select(sock+1,&fds,NULL,NULL,&tv);
        if(ret < 0){
            printf("select error %s\n",strerror(errno));
            return -1;
        }
        else if(ret == 0){
            printf("select time out\n");
            continue;
        }

        rcvlen = recv(sock,&buf,sizeof(buf),0);
        if(rcvlen > 0){
            printf("recv=%s\n",buf);
        }
    }
    close(sock);

}