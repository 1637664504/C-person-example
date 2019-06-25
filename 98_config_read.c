/*
/var/pppoe_mac_config
[user_pass]xx:xx:xx:xx:xx:xx
[cai_cai]00:0c:29:4e:0a:82

read/wirte实现
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char **argv)
{
    char str[128]={0};
    char user[16]="cai";
    char pass[16]="cai";
    char mac[32]="00:0c:29:4e:0a:82";
    char buf[128]={0};
    
    int fd,len=0,i=0;
    int len1,len2;
    FILE *fp;
    len=sprintf(buf,"[%s_%s]%s\n",user,pass,mac);

    fp = fopen("pppoe_mac_config","w+");
    //fwrite(buf,len,1,fp);
    fputs(buf,fp);

    //read
    //memset(user,0,16);
    //memset(pass,0,16);
    memset(mac,0,16);
    memset(buf,0,16);
    len1=sprintf(str,"[%s_%s]",user,pass);

    while(fgets(buf,128,fp)){
        printf("i=%d buf=%s",i++,buf);
        if(0 == strncmp(str,buf,len1)){
            strcpy(mac,buf+len1);
            len=strlen(mac);
            mac[len-1]='\0';
            printf("mac=%s\n",mac);
        }
   }
}


