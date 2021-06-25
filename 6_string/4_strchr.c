#include<stdio.h>
#include<string.h>
#include <unistd.h>
#include<stdlib.h>

#define BUFF_LEN 256
void jrd_dns_filter(char* url)
{
	char cmd_buf[BUFF_LEN] = {0};
	char dnsUrl[BUFF_LEN] = {0};
	char dnsReq[BUFF_LEN] = {0};
	char *p_start = NULL;
	char *p_end = NULL;
	unsigned int len = 0;

	strncpy(dnsUrl,url,BUFF_LEN);
	p_start = dnsUrl;
	//skip domain www
	if(strstr(dnsUrl,"www.")){
		p_start=dnsUrl + 4;
	}

	while(*p_start && (p_end=strchr(p_start,'.'))){
		*p_end='\0';
		len+=snprintf(dnsReq+len,BUFF_LEN-len,"|%0.2x|%s",p_end - p_start,p_start);
		p_start = p_end+1;
	}
	snprintf(dnsReq+len,BUFF_LEN-len,"|%0.2x|%s",strlen(p_start),p_start);


	snprintf(cmd_buf, BUFF_LEN, "iptables -I dns_filter_rule -p udp --dport 53 -m string --hex-string \"%s\" --algo bm -j DROP",dnsReq);
	printf("%s\n",cmd_buf);
	system(cmd_buf);

	memset(cmd_buf,0,sizeof(cmd_buf));
	snprintf(cmd_buf, BUFF_LEN, "ip6tables -A dns_filter_rule_6 -p udp --dport 53 -m string --hex-string \"%s\" --algo bm -j DROP",dnsReq);
	printf("%s\n",cmd_buf);
	system(cmd_buf);

	//sleep(1);
	//system(cmd_buf);

}

int main()
{

	char *buf[20]={
	"alcachondeo.com",
	"famososhonduras.videosimprevistos.rocks",
	"hn.chatmaduras.net",
	"hn.enamorados.club",
	"hn.sexlist.club",
	"prepagoshonduras.com",
	"www.chatsexohonduras.com",
	"www.citashonduras.net",
	"www.fuckbookhonduras.com",
	"www.lenceria.hn",
	"www.madurashonduras.com",
	"www.sexoenhonduras.com",
	"www.swingershonduras.com",
	"hn.ivoox.com",
	"hondurola.com",
	"hrnradiohonduras.stream",
	"livehn.stereosantacruzhn.com",
	"youtu.be",
	"youtubei.googleapis.com",
	"yt3.ggpht.com"
	};

	//jrd_dns_filter("yt3.ggpht.com");

	int i=0;
	system("iptables -t filter -D FORWARD -j dns_filter_rule");
	system("iptables -t filter -F dns_filter_rule");
	system("iptables -t filter -X dns_filter_rule");
    system("iptables -t filter -N dns_filter_rule");
    system("iptables -t filter -A INPUT -j dns_filter_rule");

	system("ip6tables -t filter -D INPUT -j dns_filter_rule_6");
	system("ip6tables -t filter -F dns_filter_rule_6");
	system("ip6tables -t filter -X dns_filter_rule_6");
    system("ip6tables -t filter -N dns_filter_rule_6");
    system("ip6tables -t filter -A INPUT -j dns_filter_rule_6");


	while(i<20){
	jrd_dns_filter(buf[i]);
	i++;
	}

}
