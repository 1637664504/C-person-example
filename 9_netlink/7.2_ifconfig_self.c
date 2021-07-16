#include <stdio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    E_LINK_NO_CARRIER,
    E_LINK_UP,
    E_LINK_DOWN,
}e_link_status_t;

int main()
{
    struct ifreq ifr={0};
    int ret;
    unsigned int flags;
    int running=0;
    int fd = 0;
    //1. 创建DGRAM 套接字
    fd =socket(AF_INET,SOCK_DGRAM,0);

    //2. ifr_name 填充
    strncpy(ifr.ifr_name,"eth2",4);
    //3. ioctl() 选项
    ret = ioctl(fd,SIOCGIFFLAGS,&ifr);

    //4.获取
    flags = ifr.ifr_flags;
    if((flags & IFF_UP) && !(flags & IFF_RUNNING))
    {
        ret = E_LINK_NO_CARRIER;
    }
    else if((flags & IFF_UP) && (flags & IFF_RUNNING))
    {
        ret = E_LINK_UP;
    }
    else if(!(flags & IFF_UP))
    {
        ret = E_LINK_DOWN;
    }
    printf("link flag=%x status=%d\n",flags, ret);

    return 0;
}
/*
flags reuslt as:

Link status:up          down
insert      0x1043      0x1002
Not insert  0x1003      0x1002
*/