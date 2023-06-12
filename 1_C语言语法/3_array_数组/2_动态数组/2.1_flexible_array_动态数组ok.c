/*
可编数组, 柔性数组
*/
#include <stdio.h>
#include <stdlib.h>
struct client_info{
    int count;
    int fd[];
};

int main()
{
    struct client_info *tmp;
    tmp = malloc(sizeof(*tmp)+sizeof(int)*10);
    tmp->count = 10;

    for(int i=0;i<tmp->count;i++){
        tmp->fd[i] = i;
    }

    for(int i=0;i<tmp->count;i++){
        printf("%d: fd=%d \n",i,tmp->fd[i]);
    }

    free(tmp);

    return 0;
}

/*
结果: OK
*/