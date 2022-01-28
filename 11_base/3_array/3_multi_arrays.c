/*
Two dimensional array
测试二维数组做参数
*/
#include <stdio.h>
void fun(int a[][10],int len)
{
    int i,j;
    for(i=0;i<len;i++)
    {
        for(j=0;j<10;j++)
            a[i][j] = i*10+j;
    }
}

void dump_hex_int(int *a,int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        printf("%0.2d ",*(a+i));
        if(i%10 == 9){
            printf("\n");
        }
    }
}

int main()
{
    int a[5][10];
    fun(a,sizeof(a)/sizeof(a[0]));
    dump_hex_int((int *)a,sizeof(a)/sizeof(a[0][0]));

    return 0;
}