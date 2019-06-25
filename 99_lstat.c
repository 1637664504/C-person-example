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
    struct stat buf;
    int ret;
    ret = lstat("1.c",&buf);
    if(ret < 0){
        perror("lstate 1.c error");
    }

    ret = lstat("liuj.c",&buf);
    if(ret < 0){
        perror("lstate liuj.c error");
    }

    return 0;
}

