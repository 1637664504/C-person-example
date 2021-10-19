
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main ( int argc, char *argv[] )
{
    int a=4;
    void *p;
    
    p = &a;
    printf("p=%d\n",*(int *)p);
    //printf("p=%d\n",(int *)(*p));
    //printf("p=%d\n",(int)(*p));
    //printf("p=%d\n",*(int *p));

    return 0;
}