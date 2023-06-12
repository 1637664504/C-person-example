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
    struct client_info tmp;
    tmp.fd = malloc(sizeof(int)*10);

    for(int i=0;i<10;i++){
        tmp.fd[i] = i;
    }
    return 0;
}

/*
结果: 编译报错，无法支持
2_flexible_array.c:15:12: error: invalid use of flexible array member
   15 |     tmp.fd = malloc(sizeof(int)*10);
      |            ^

*/