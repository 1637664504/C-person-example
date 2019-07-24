#include<stdio.h>

int add(int a,int b)
{
    return a+b;
}
int  main(void)
{
    int a=0,b=0;
    int c=1;
    while(1){
        a+=2;
        b+=5;
        printf("a=%d,b=%d\n",a,b);
        c=add(a,b);
        sleep(c);
    }
}
