#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>


int main ( int argc, char *argv[] )
{
    if(argc != 2)
    {
        printf("Usage: %s file\n",argv[0]);
        exit(-1);
    }

    char *file = argv[1];
    int ret = 0;
    struct stat fp_stat;

    ret = stat(file, &fp_stat);
    if (ret)
    {
        printf("open fail %d=%s\n",errno, strerror(errno));
        return -1;
    }

    int mode = fp_stat.st_mode;
    printf("st_mode=%x\n",fp_stat.st_mode);
    if(S_ISDIR(mode))
        printf("is dis\n");
    else if(S_ISCHR(mode))
        printf("is chr\n");
    else if(S_ISBLK(mode))
        printf("is blk\n");
    else if(S_ISLNK(mode))
        printf("is lnk\n");
    else if(S_ISSOCK(mode))
        printf("is sock\n");
    else if(S_ISFIFO(mode))
        printf("is fifo\n");
    
    printf("at_time=%ld\n",fp_stat.st_atim.tv_sec);  //访问 时间，影响性能，一般的linux发行版本不开启，
    printf("mt_time=%ld\n",fp_stat.st_mtim.tv_sec);  //owner, group, permission 修改时间
    printf("ct_time=%ld\n",fp_stat.st_ctim.tv_sec);  //内容 修改时间

    return 0;
}
