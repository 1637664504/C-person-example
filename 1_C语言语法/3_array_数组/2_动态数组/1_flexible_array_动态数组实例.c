#include<stdio.h>
#include<malloc.h>
typedef struct _SoftArray {
    int len;
    int array[];
}SoftArray;

int main()
{
    int len = 10, i = 0;

    SoftArray* p = (SoftArray*)malloc(sizeof(SoftArray) + sizeof(int) * len);
    p->len = len;

    for (i = 0;i < 11;i++)
    {
        p->array[i] = i + 1;
    }
    for (i = 0;i < 11;i++)
    {
        printf("%d\n", p->array[i]);
    }

    free(p);

    return 0;
}