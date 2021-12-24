#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//void show_list(const char (*dns_array)[40], int count)
void show_list(const char dns_array[][40], int count)
{
    int i;
    for(i=0;i<count;i++)
    {
        printf("%d=%s\n",i,dns_array[i]);
    }
}

int main ( int argc, char *argv[] )
{
    char list[4][40]={"223.5.5.5","8.8.8.8","2400:3200::1","2400:3200:baba::1"};
    //show_list(list,4);
    show_list(list,sizeof(list)/sizeof(list[0]));

    return 0;
}