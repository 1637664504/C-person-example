#include <stdio.h>
#include <string.h>
#include <unistd.h>

char pptp_server[64];

int  getPptpService_addr(int argc, char **argv,char *pptp_server)
{
	char *arg;

	while(argc > 0){
		arg = *argv++;
		argc--;

		if(!strcmp("pptp_server",arg)){
			strcpy(pptp_server,*(argv++));
			printf("liuj-- pptp_server=%s\n",pptp_server);
			return 1;
		}
	}

	return 0;
}

int main(int argc, char *argv[])
{
	int ret;
	printf("liuj-- 1111111\n");

	ret = getPptpService_addr(argc,argv,pptp_server);
	if(ret)
		printf("liuj-- 22222222\n");
	else
		printf("liuj-- 3333333\n");

	char *p = argv[argc-1];
	char buf[16]={0};
	strcpy(buf,p);
	printf("liuj-- 44 p=%s, buf=%s\n",p,buf);

	system("ls /dev;ls ~");

}


