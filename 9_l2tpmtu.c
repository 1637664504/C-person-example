
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
   int l2tpMtu_fd;
   if(mkdir(L2TP_PATH,0771) < 0){
        cmsLog_debug("mkidr /data/ppp failed!\n");    
   }
   unlink(L2TP_MTU);
   if((l2tpMtu_fd = open(L2TP_MTU,O_RDWR|O_CREAT,0664)) < 0){
        cmsLog_debug("open /data/ppp/l2tp.mtu failed!\n");    
   }
   write(l2tpMtu_fd,&l2tpmtu,sizeof(int));
   
   //read test
   /*
   int tmp;
   char mtu_buf[16]={0};
   read(l2tpMtu_fd,&tmp,sizeof(tmp));
   sscanf(mtu_buf,"%d",&tmp);
   printf("mtu_buf=%s\n",mtu_buf);
   */
 return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

