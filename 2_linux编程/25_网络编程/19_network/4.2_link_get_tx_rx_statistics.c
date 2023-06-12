#include <stdio.h>
#include <string.h>

#define SYS_USAGE_FILE "/proc/net/dev"
struct link_statistics{
    unsigned long rx_bytes;
    unsigned long rx_packets;
    unsigned long rx_errs;
    unsigned long tx_bytes;
    unsigned long tx_packets;
    unsigned long tx_errs;
};

int get_link_statistics(const char *ifname,struct link_statistics *info)
{
    int ret = 0;
    FILE *fp;
    unsigned long rx_bytes, rx_packets, rx_errs, rx_drops,
		rx_fifo, rx_frame,
		tx_bytes, tx_packets, tx_errs, tx_drops,
		tx_fifo, tx_colls, tx_carrier, rx_multi;
    
    
    fp = fopen(SYS_USAGE_FILE,"r");
    if(!fp)
    {
        perror("System no support.");
        return -1;
    }

    char buf[256] = {0};
    while(fgets(buf,sizeof(buf)-1,fp)){
        if(strstr(buf,ifname)){
            if (sscanf(buf, "%*[^:]:%lu%lu%lu%lu%lu%lu%lu%*d%lu%lu%lu%lu%lu%lu%lu",
			   &rx_bytes, &rx_packets, &rx_errs, &rx_drops,
			   &rx_fifo, &rx_frame, &rx_multi,
			   &tx_bytes, &tx_packets, &tx_errs, &tx_drops,
			   &tx_fifo, &tx_colls, &tx_carrier) == 14)
            {
                printf("rx=%lu, %lu, tx=%lu,%lu\n",rx_bytes,rx_packets,tx_bytes,tx_packets);
                info->rx_bytes = rx_bytes;
                info->rx_packets = rx_packets;
                info->rx_errs = rx_errs;
                info->tx_bytes = tx_bytes;
                info->tx_packets = tx_packets;
                info->tx_errs = tx_errs;
            }
            else
            {
                ret = -2;
            }
            break;
        }
    }
    return ret;
}

int main(int argc, char *argv[])
{
    struct statistics info = {0};
    char ifname[16] = "eth1";
    get_link_statistics(ifname,&info);

    return 0;
}