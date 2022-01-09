#include <stdio.h>
#include "sort_array.h"

#if debug
//un-know move number，usring two variable move
int array_move_right(int a[],int len)
{
    int i;
    int last=a[0];
    int now;
    for(i=0;i<len;i++)
    {
        now = a[i+1];
        a[i+1] = last;
        last = now;
    }
}
#endif

//know move number
void array_move_right(int a[],int len)
{
    int i;
    for(i=len;i>0;i--)
    {
        a[i]=a[i-1];
    }
    a[0] = 0;
}

void array_move_left(int a[],int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        a[i-1] = a[i];
    }
    a[i-1] = 0;
}

void array_move(int a[],int len,enum array_move_direct direct)
{
    if(direct == ARRAY_LEFT_MOVE)
        array_move_left(a,len);
    else if(direct == ARRAY_RIGHT_MOVE)
        array_move_right(a,len);
}


int array_insert_sort(int a[], unsigned int count, int number)
{
    int ret = -1;
    int i;

    array_dump(a,count);
    for(i=0;i<=count;i++){
        if(i == count)
        {
            a[i] = number;
            ret = 0;
            break;
        }

        if(a[i] > number)
        {
            array_move_right(&a[i],count-i);
            a[i] = number;
            ret = 0;
            break;
        }
    }

    return ret;
}

int array_del_sort(int a[], unsigned int len, int number)
{
    int ret = -1;
    int i;
    for(i=0;i<len;i++){
        if(a[i] > number)
        {
            array_move_left(&a[i],len-i);
            ret = 0;
            break;
        }
    }

    return ret;
}

void array_dump(int a[],int len)
{
    int i;
    for(i=0;i<len;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}

#if UNIT_TEST
int main(void)
{
    int array[16]={1,3,5,7,9};
    int number = 8;
    array_show(array,5);
    array_insert_sort(array,5,4);
    array_del_sort(array,6,4);
    array_show(array,6);
    return 0;
}
#endif
