
#include <linux/netlink.h>
//iplink_get(filter_dev, RTEXT_FILTER_VF)
struct iplink_req {
	struct nlmsghdr		n;
	struct ifinfomsg	i;
	char			buf[1024];
};

int iplink_get(char *name, __u32 filt_mask)
{
	struct iplink_req req = {
		.n.nlmsg_len = NLMSG_LENGTH(sizeof(struct ifinfomsg)),
		.n.nlmsg_flags = NLM_F_REQUEST,
		.n.nlmsg_type = RTM_GETLINK,
		.i.ifi_family = preferred_family,
	};
	struct nlmsghdr *answer;

	if (name) {
		addattr_l(&req.n, sizeof(req),
			  !check_ifname(name) ? IFLA_IFNAME : IFLA_ALT_IFNAME,
			  name, strlen(name) + 1);
	}
	addattr32(&req.n, sizeof(req), IFLA_EXT_MASK, filt_mask);

	if (rtnl_talk(&rth, &req.n, &answer) < 0)
		return -2;

	//open_json_object(NULL);
	print_linkinfo(answer, stdout);
	//close_json_object();

	free(answer);
	return 0;
}


int main(void)
{
    iplink_get("eth1",RTEXT_FILTER_VF);
}
