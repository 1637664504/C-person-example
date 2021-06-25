#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include<linux/netlink.h>

int main()
{
    int ret;
    //1.netlink sock
    int fd;
    fd_set fds;
    int buffsize=1024;

    fd = socket(AF_NETLINK,SOCK_RAW,NETLINK_KOBJECT_UEVENT);
    if(fd < 0){
        perror("create sock failed.");
        exit(-1);
    }
    setsockopt(fd,SOL_SOCKET,SO_RCVBUF,&buffsize,sizeof(buffsize));

    //2.netlink addr
    struct sockaddr_nl sa;
    memset(&sa,0,sizeof(sa));
    sa.nl_family = AF_NETLINK;
    sa.nl_pid = getpid();
    sa.nl_groups = 1;

    //3.bind
    if(bind(fd,(struct sockaddr*)&sa,sizeof(sa))){
        perror("bind error");
        exit(-1);
    }

    //4.select
    while(1){
        char buf[1024]={0};
        struct timeval tv;
        int len=0;

        tv.tv_sec=5;
        tv.tv_usec=0;
        FD_ZERO(&fds);
        FD_SET(fd,&fds);

        //4.1 select
        ret = select(fd+1,&fds,NULL,NULL,&tv);
        if(ret < 0){
            perror("select fail");
            return -1;
        }
        else if(ret == 0){
            printf("timeout\n");
            continue;
        }
        printf("fd is set\n");
        len = recv(fd,&buf,sizeof(buf),0);
        if(len > 0){
            printf("recv=%s len=%d\n",buf,len);
        }

    }
    close(fd);
}