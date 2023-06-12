/*
1.此代码参考busybox ifconfig实现, 读取与解析 /proc/net/dev

to do
ip link(即netlink)也可以获取此参数，尝试使用ip link获取

*/

#include <stdio.h>
#include <string.h>
#include <errno.h>

#define SYS_PATH_PROCNET_DEV		"/proc/net/dev"

struct net_device_stats {
    unsigned long long rx_packets;	/* total packets received       */
    unsigned long long tx_packets;	/* total packets transmitted    */
    unsigned long long rx_bytes;	/* total bytes received         */
    unsigned long long tx_bytes;	/* total bytes transmitted      */
    unsigned long rx_errors;	/* bad packets received         */
    unsigned long tx_errors;	/* packet transmit problems     */
    unsigned long rx_dropped;	/* no space in linux buffers    */
    unsigned long tx_dropped;	/* no space available in linux  */
    unsigned long rx_multicast;	/* multicast packets received   */
    unsigned long rx_compressed;
    unsigned long tx_compressed;
    unsigned long collisions;

    unsigned long rx_frame_errors;	/* recv'd frame alignment error */
    unsigned long rx_fifo_errors;	/* recv'r fifo overrun          */

    unsigned long tx_carrier_errors;
    unsigned long tx_fifo_errors;
};

int get_net_device_stats(const char *ifname, struct net_device_stats *stats)
{
    FILE *fh;
    char buf[128];
    //char dev[16];
    struct interface *ife;
    int err;

    fh = fopen(SYS_PATH_PROCNET_DEV, "r");
    if (!fh) {
		fprintf(stderr, "Warning: cannot open %s (%s). Limited output.\n",
			SYS_PATH_PROCNET_DEV, strerror(errno));
		return -2;
	}
    if (fgets(buf, sizeof buf, fh))
		/* eat line */;
    if (fgets(buf, sizeof buf, fh))
		/* eat line */;


    err = 0;
    while (fgets(buf, sizeof buf, fh)) {
        if(strstr(buf,ifname))
        {
            sscanf(buf,"%*[^:]: %Lu %Lu %lu %lu %lu %lu %lu %lu %Lu %Lu %lu %lu %lu %lu %lu %lu",
           //dev,
	       &stats->rx_bytes,
	       &stats->rx_packets,
	       &stats->rx_errors,
	       &stats->rx_dropped,
	       &stats->rx_fifo_errors,
	       &stats->rx_frame_errors,
	       &stats->rx_compressed,
	       &stats->rx_multicast,

	       &stats->tx_bytes,
	       &stats->tx_packets,
	       &stats->tx_errors,
	       &stats->tx_dropped,
	       &stats->tx_fifo_errors,
	       &stats->collisions,
	       &stats->tx_carrier_errors,
	       &stats->tx_compressed);

           break;
        }
    }

    fclose(fh);
}

int main(int argc, char *argv[])
{
    struct net_device_stats stats = {0};
    get_net_device_stats("ppp0",&stats);
    printf("%lu, %lu \n",stats.rx_bytes,stats.tx_bytes);
    return 0;
}