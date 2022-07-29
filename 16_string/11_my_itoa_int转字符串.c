/*
int 转 字符串
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define str_zero '0'
#define MAXLEN 128
int my_itoa(int num, char *str)
{
    char a[MAXLEN+1]="";
    int x = num;
    int y;
    int i=0;
    int ret = -1;

    //负数判断
    if(num<0){
        x=0-num;
    }

    while(x>10)
    {
        y=x%10;
        x=x/10;
        a[i]= str_zero + y;
        i++;
        if(i>=MAXLEN)
        {
            printf("error, num over max str leng %d",MAXLEN);
            return -1;
        }
    }
    a[i]=str_zero + x;

    int j=0;
    if(num<0)
    {
        *(str)='-';
        j++;
    }
    //rever str
    for(;i>=0;i--){
        *(str+j)=a[i];
        j++;
    }
	*(str+j)='\0';

    printf("a=%s,str=%s\n",a,str);

    return 0;
}

int main()
{
    char str[64]="";

    my_itoa(123,str);
    my_itoa(-123,str);
	my_itoa(123456789,str);
	my_itoa(-123456789,str);

	my_itoa(0,str);
	my_itoa(-1,str);
	my_itoa(1,str);

    return 0;
}