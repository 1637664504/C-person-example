#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>



int main(int argc,char *argv[])
{
    char mac[64]="C8:3A:35:14:4C:58";
    unsigned int num[6];
	sscanf(mac,"%x:%x:%x:%x:%x:%x",&num[0],&num[1],&num[2],&num[3],&num[4],&num[5]);
    printf("f=%x\n",num[5]); 
    num[5] += 0x3;
    memset(mac,'\0',64);
    sprintf(mac,"%x:%x:%x:%x:%x:%x",num[0],num[1],num[2],num[3],num[4],num[5]);
    printf("obj->mac=, default wan mac=%s",mac);
}


