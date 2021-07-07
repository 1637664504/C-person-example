#include <stdio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    struct ifreq ifr={0};
    int ret;
    int flags;
    int running=0;
    int fd = 0;
    //1. 创建DGRAM 套接字
    fd =socket(AF_INET,SOCK_DGRAM,0);

    //2. ifr_name 填充
    strncpy(ifr.ifr_name,"eth2",4);
    //3. ioctl() 选项
    ret = ioctl(fd,SIOCGIFFLAGS,&ifr);

    //4.获取
    flags=ifr.ifr_flags;
	if(flags & IFF_RUNNING)	
	{
		running = 1;	
	}
    printf("flag=%x, runing=%d",flags,running);

    return 0;
}