/*
select()监听stdin   可读

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DEBUG
#ifdef DEBUG
#define debug printf
#else
#define debug
#endif
#define BUF_LEN 512

int main(int argc,char *argv[])
{
	fd_set reads,tmps;
	int ret,maxfd,i,len;
	struct timeval ts;
	FD_ZERO(&reads);
	FD_SET(STDIN_FILENO,&reads);

	maxfd=0;
	while(1){
		tmps = reads;
		ts.tv_sec=5;
		ts.tv_usec=0;
		ret = select(maxfd+1,&tmps,NULL,NULL,&ts);
		if(ret == -1){
			perror("select fail");
			return 0;
		}else if(ret == 0){
			debug("select timeout\n");
			continue;
		}
		for(i=0;i<maxfd+1;i++){
			if(!FD_ISSET(i,&tmps)){
				continue;
			}
			if(i == STDIN_FILENO){
				char msg[BUF_LEN]={0};
				debug("stdin can read\n");
				len = read(i,msg,BUF_LEN);
				printf("--len %d:%s--",len,msg);
			}

		}

	}

	return 0;
}



