#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/if_packet.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include "common/network/network.h"
#define LISTEN_INTERFACE "eth2"

struct raw_packs{
    char *data;
    ssize_t len;
};

int check_dhcp_request(struct raw_packs* packs)
{
    ethhdr_t *eth_header = NULL;
    iphdr_t *ip_header = NULL;
    ssize_t ip_header_len = 0;

    eth_header = (ethhdr_t *)(packs->data);
    ip_header = (iphdr_t *)(packs->data + ETH_HEAD_LEN);
    ip_header_len =  (ip_header->h_verlen & 0x0f) * 4;

    if (ip_header->protocol == IPPROTO_UDP)
    {
        udphdr_t *udp_header = (udphdr_t *)(packs->data + ETH_HEAD_LEN + ip_header_len);
        unsigned short sport = ntohs(udp_header->sport);
        unsigned short dport = ntohs(udp_header->dport);
        if (sport == 68 && dport == 67)
        {
            printf("Receive dhcp request.\n");
        }
    }

    return 0;
}

int listen_socket_init(void)
{
    struct ifreq ifr;
    struct sockaddr_ll sll;
    int sock_fd;

    /* capture ip datagram without ethernet header */    
    sock_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP));
    if (sock_fd < 0)
    {
        perror("create socket failed\n");
        return -1;
    }

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, LISTEN_INTERFACE, sizeof(ifr.ifr_name));
    if (ioctl(sock_fd, SIOCGIFINDEX, &ifr) == -1)
    {
        printf("ioctl failed:%s\n", strerror(errno));
        ret = -1;
    }

    memset(&sll, 0, sizeof(sll));
    sll.sll_family = AF_PACKET;
    sll.sll_ifindex = ifr.ifr_ifindex;
    sll.sll_protocol = htons(ETH_P_ALL);
    if (bind(sock_fd, (struct sockaddr *)&sll, sizeof(sll)) < 0)
    {
        printf("bind failed:%s\n", strerror(errno));
        ret = -1;
    }

    return sock_fd;
}

int listen_lan_interface_dhcp()
{

}

void* lan_listen_dhcp_thread(void *arg)
{
    char recv_buf[2048];
    struct timeval tm;
    int sock_fd;
    int max_fd;
    ssize_t recv_size = 0;
    struct raw_packs packs;
    fd_set fds;
    int ret;

    sock_fd = listen_socket_init();
    if(sock_fd < 0)
    {
        printf("socket socket failed\n");
        exit(-1);
    }
    max_fd = sock_fd;

    while (1)
    {
        FD_ZERO(&fds);
        FD_SET(sock_fd, &fds);
        tm.tv_sec = 8;

        ret = select(max_fd + 1, &fds, NULL, NULL, &tm);
        if(ret < 0)
        {
            printf("select failed:%s\n", strerror(errno));
            exit(-1);
        }
        else if(ret == 0)
        {
            printf("select timeout\n");
            continue;
        }
        if(FD_ISSET(sock_fd, &fds))
        {
            memset(recv_buf,0,sizeof(recv_buf));
            recv_size = recv(sock_fd, recv_buf, sizeof(recv_buf)-1, 0);
            if (recv_size == -1)
            {
                printf("recv error:%s\n", strerror(errno));
                ret = -1;
            }
            else if (recv_size > 82)
            {
                packs.data = recv_buf;
                packs.len = recv_size;
                check_dhcp_request(&packs);
            }
        }
    }

}

#if 1
int main(void)
{
    pthread_t tid;
    void **retval;
    struct thread_manage lan_listen_thread_manage;

    thread_manage_init(&lan_listen_dhcp_thread);
    int status = pthread_create(&tid, NULL, lan_listen_dhcp_thread, &lan_listen_thread_manage);
    if(status != 0)
    {
        perror("pthread_create error");
    }
    pthread_detach(tid);  //1. 不阻塞，线程独立运行
    //pthread_join(tid,&ret); //2. 阻塞，直到子线程结束， **ret保持线程返回值

    char cmd[16];
    while(1)
    {
        printf("please inpud cmd: s-stop r-runing\n");
        scanf("%s",cmd);
        if(cmd[0] == 'r')
        {
            thread_manage_wakeup(&lan_listen_thread_manage);\
        }
        else if(cmd[0] == 's')
        {
            thread_manage_stop(&lan_listen_thread_manage);
        }
        else if(cmd[0] == 'e')
        {
            exit(0);
        }
        else if(cmd[0] == 'l')
        {
            printf("task state=%d\n",lan_listen_thread_manage.state);
        }
    }
}
#endif