
#include	<stdlib.h>
#include    <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#if 0
#define L2TP_PATH "/data/ppp"
#define L2TP_MTU "/data/ppp/l2tp.mtu"
#else
#define L2TP_PATH "/home/liuj/ppp"
#define L2TP_MTU "/home/liuj/ppp/l2tp.mtu"
#endif
#define cmsLog_debug printf
int l2tpmtu = 1460;

int main ( int argc, char *argv[] )
{
   //read test
  int l2tpMtu_fd;
  if((l2tpMtu_fd = open(L2TP_MTU,O_RDWR|O_CREAT,0664)) < 0){
        cmsLog_debug("open /data/ppp/l2tp.mtu failed!\n");    
   }
   int tmp;
   char mtu_buf[16]={0};
   read(l2tpMtu_fd,&tmp,sizeof(tmp));
   sprintf(mtu_buf,"%d",tmp);
   printf("tmp=%d, mtu_buf=%s\n",tmp,mtu_buf);
   
 return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

