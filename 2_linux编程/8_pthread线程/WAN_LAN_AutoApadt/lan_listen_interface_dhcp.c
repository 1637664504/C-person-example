#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/if_packet.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include "sys_thread.h"
#include "common/network/sys_network.h"
#include "monitor_interface_netlink.h"
#define LISTEN_INTERFACE "eth2"

#ifdef DEBUG
#define UNIT_TEST 1
#endif

struct raw_packs{
    char *data;
    ssize_t len;
};

int check_dhcp_request(struct raw_packs* packs)
{
    unsigned char link_mac[IFHWADDRLEN] = {0};
    ethhdr_t *eth_header = NULL;
    iphdr_t *ip_header = NULL;
    ssize_t ip_header_len = 0;
    int ret = 0;

    eth_header = (ethhdr_t *)(packs->data);
    get_link_mac(LISTEN_INTERFACE,link_mac,IFHWADDRLEN);
    if(memcmp(eth_header->src_mac,link_mac,IFHWADDRLEN) == 0)
        return 0;

    ip_header = (iphdr_t *)(packs->data + ETH_HEAD_LEN);
    ip_header_len =  (ip_header->h_verlen & 0x0f) * 4;
    if (ip_header->protocol == IPPROTO_UDP)
    {
        udphdr_t *udp_header = (udphdr_t *)(packs->data + ETH_HEAD_LEN + ip_header_len);
        unsigned short sport = ntohs(udp_header->sport);
        unsigned short dport = ntohs(udp_header->dport);

        if (sport == 68 && dport == 67)
        {
            printf("LAN Receive dhcp request.\n");
            ret = 1;
        }
    }

    return ret;
}

static int listen_interfece_sock_init(const char* ifcname)
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
    strncpy(ifr.ifr_name, ifcname, sizeof(ifr.ifr_name));
    if (ioctl(sock_fd, SIOCGIFINDEX, &ifr) == -1)
    {
        printf("ioctl failed:%s\n", strerror(errno));
        return -1;
    }

    memset(&sll, 0, sizeof(sll));
    sll.sll_family = AF_PACKET;
    sll.sll_ifindex = ifr.ifr_ifindex;
    sll.sll_protocol = htons(ETH_P_ALL);
    if (bind(sock_fd, (struct sockaddr *)&sll, sizeof(sll)) < 0)
    {
        printf("bind failed:%s\n", strerror(errno));
        return -1;
    }

    return sock_fd;
}

void* listen_interface_dhcp_thread(void *arg)
{
    char recv_buf[2048];
    struct timeval tm;
    int sock_fd;
    int max_fd;
    ssize_t recv_size = 0;
    struct raw_packs packs;
    fd_set fds;
    int check_dhcp_result;
    int ret;
    #if UNIT_TEST
    struct thread_manage *thread = (struct thread_manage *)arg;
    sock_fd = listen_interfece_sock_init("eth2");

    #else
    struct monitor_thread *thread_info = (struct monitor_thread *)arg;
    struct thread_manage *thread = &thread_info->lan_manage;
    char *listen_ifcname = thread_info->ifcname;

    sock_fd = listen_interfece_sock_init(listen_ifcname);
    #endif
    if(sock_fd < 0)
    {
        printf("socket socket failed\n");
        exit(-1);
    }
    max_fd = sock_fd;

    while (1)
    {
        printf("LAN st=%d\n",thread->state);
        if(thread->state != thread_running)
        {
            printf("LAN task: %s suspend\n",__func__);
            thread_manage_suspend(thread, 0);
            printf("LAN dhcp task: wake up\n");
        }
        printf("LAN start\n");
        //re-start thread init
        check_dhcp_result = 0;
        ret = -1;
        memset(&tm,0,sizeof(tm));

        FD_ZERO(&fds);
        FD_SET(sock_fd, &fds);
        tm.tv_sec = 8;
        tm.tv_usec=0;

        ret = select(max_fd + 1, &fds, NULL, NULL, &tm);
        if(ret < 0)
        {
            printf("LAN select failed:%s\n", strerror(errno));
            exit(-1);
        }
        else if(ret == 0)
        {
            printf("LAN listen dhcp select timeout\n");
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
                check_dhcp_result = check_dhcp_request(&packs);
            }
        }

        if(check_dhcp_result)
        {
            //监听到dhcp request
            //1.send msg to ubus
            //2.stop listen interface thread.
            printf("LAN recv dhcp request ret=%d\n",ret);
            thread_manage_stop(thread);
            send_cmd_to_main_thread(thread_info,CMD_LAN_FINISH);
        }

    }

}

int lan_listen_dhcp_thread_manage_create(struct monitor_thread *thread_info)
{
    pthread_t tid;
    int status = -1;

    if(!thread_info)
        return -1;

    thread_manage_init(&thread_info->lan_manage);
    status = pthread_create(&tid, NULL, listen_interface_dhcp_thread, thread_info);
    if(status != 0)
    {
        perror("pthread_create error");
    }
    pthread_detach(tid);

    return 0;
}

#if UNIT_TEST
int main(void)
{
    pthread_t tid;
    struct thread_manage lan_listen_thread_manage;

    thread_manage_init(&lan_listen_thread_manage);
    int status = pthread_create(&tid, NULL, listen_interface_dhcp_thread, &lan_listen_thread_manage);
    if(status != 0)
    {
        perror("pthread_create error");
    }
    pthread_detach(tid);

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