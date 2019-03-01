#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
int main(int argc,char *argv[])
{
	int sock;
	sock = socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
}

