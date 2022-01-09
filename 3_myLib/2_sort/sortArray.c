#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort_array.h"
#include "sortArray.h"

int sortArray_insert_number(struct sortArray *a,int number)
{
    int ret = -1;
    if(a->count == a->MaxNumber)
        return -1;

    if(array_insert_sort(a->array, a->count, number) == 0)
    {
        a->count++;
        ret = 0;
    }

    return ret;
}

int sortArray_delete_number(struct sortArray *array,int number)
{
    int ret = -1;
    if(array->count == 0)
        return -1;

    if(array_del_sort(array->array, array->count, number) == 0)
    {
        array->count --;
        ret = 0;
    }

    return ret;
}

void sortArray_show(struct sortArray *a)
{
    int i;

    if(!a)
        return;

    for(i=0;i<a->count;i++)
    {
        printf("-- %d ",a->array[i]);
    }
    printf("\n");
}

int sortArray_init(struct sortArray **a, int number)
{
    int ret = -1;

    if(!a)
        return -1;

    *a = malloc(sizeof(struct sortArray) + sizeof(int)*number);
    if(*a)
    {
        (*a)->MaxNumber = number;
        (*a)->count = 0;
        (*a)->add = sortArray_insert_number;
        (*a)->del = sortArray_delete_number;
        (*a)->show = sortArray_show;
        memset((*a)->array,0,sizeof(int)*number);
        ret = 0;
    }

    return ret;
}

void sortArray_release(struct sortArray *a)
{
    if(a)
    {
        free(a);
        a = NULL;
    }
}