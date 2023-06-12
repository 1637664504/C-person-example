/*
 *  List all network interfaces
 */
#include <stdio.h>
#include <stdlib.h>
#include <netlink/netlink.h>
#include <netlink/genl/genl.h>

static int print_link(struct nl_msg * msg, void * arg)
{
    struct nlmsghdr * h = nlmsg_hdr(msg);
    struct ifinfomsg * iface = NLMSG_DATA(h);
    struct rtattr * attr = IFLA_RTA(iface);
    int remaining = RTM_PAYLOAD(h);

    for (; RTA_OK(attr, remaining); attr = RTA_NEXT(attr, remaining))
    {
        switch (attr->rta_type)
        {
        case IFLA_IFNAME:
            printf("Interface %d : %s\n", iface->ifi_index, (char *)RTA_DATA(attr));
            break;
        default:
            printf("Interface %d msg=%d: %s\n", iface->ifi_index, attr->rta_type, (char *)RTA_DATA(attr));
            break;
        }
    }

    return NL_OK;
}

void die(char * s)
{
    perror(s);
    exit(1);
}

int main(void)
{
    struct nl_sock * s = nl_socket_alloc();
    if (s == NULL) {
        die("nl_socket_alloc");
    }

    if (nl_connect(s, NETLINK_ROUTE) < 0) {
        nl_socket_free(s);
        die("nl_connet");
    }

    struct rtgenmsg rt_hdr = { .rtgen_family = AF_NETLINK, };
    if (nl_send_simple(s, RTM_GETLINK, NLM_F_REQUEST|NLM_F_DUMP, &rt_hdr, sizeof(rt_hdr)) < 0) {
        nl_socket_free(s);
        die("nl_send_simple");
    }

    //Retrieve the kernel's answer.
    nl_socket_modify_cb(s, NL_CB_VALID, NL_CB_CUSTOM, print_link, NULL);
    nl_recvmsgs_default(s);

    nl_socket_free(s);
    return 0;
}