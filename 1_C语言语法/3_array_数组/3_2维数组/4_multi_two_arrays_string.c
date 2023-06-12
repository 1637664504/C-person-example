/*
Two dimensional array
测试二维数组做参数
*/
#include <stdio.h>

void print_two_arrays_string(char buf[][32],int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        printf("%s \n",buf[i]);
    }
}

void print_two_arrays_point_string(char (*buf)[32],int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        printf("%s \n",buf+i);
    }
}

int main()
{
    char a[][32]={
        "aaa",
        "bbb",
        "ccc",
        "ddd"
    };
    //print_two_arrays_string(a,sizeof(a)/sizeof(a[0]));
    print_two_arrays_point_string(a,sizeof(a)/sizeof(a[0]));

    return 0;
}