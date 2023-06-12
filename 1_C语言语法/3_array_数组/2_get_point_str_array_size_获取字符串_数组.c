/*
获取 结构体，数组的长度
*/
#include <stdio.h>

char *str_arry[3]={
    "aaaaaaa",
    "bbbbbbb",
    "ccccccc"
};

int main(void)
{
    unsigned int size;
    //1.指针数组长度
    size = sizeof(str_arry)/sizeof(str_arry[0]);
    printf("size=%u\n",size);

    return 0;
}