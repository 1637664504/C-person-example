/*
可编数组, 柔性数组

目的:
不使用指针，尝试强制使用 变量 引用可变数组

结果:
info->count 调试值为10
tmp.count 调试值为0       -->程序无法引用tmp.count

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct client_info{
    int count;
    int fd[];
};

int client_manage_init(struct client_info *info, const unsigned int number)
{
    int ret = -1;

    if(number <= 0)
        return -1;
    
    memset(info,0,sizeof(*info));
    info = malloc(sizeof(*info)+sizeof(int)*number);
    if(info)
    {
        info->count = number;
        ret = 0;
        printf("init ok\n");
    }

    return ret;
}

int main()
{
    struct client_info tmp;
    client_manage_init(&tmp,10);

    for(int i=0;i<tmp.count;i++){
        tmp.fd[i] = i;
    }

    for(int i=0;i<tmp.count;i++){
        printf("%d: fd=%d \n",i,tmp.fd[i]);
    }

    //free(tmp);

    return 0;
}

/*
结果: NG

*/