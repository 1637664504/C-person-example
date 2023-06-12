
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum{
    eth_set_lan,
    eth_set_wan,
    eth_down,
}lan_eth_function_t;

typedef enum{
    state1 = 1,
}state;

int main ( int argc, char *argv[] )
{
    printf("enum size=%lu\n",sizeof(lan_eth_function_t));
    printf("enum state size=%lu\n",sizeof(state1));

    return 0;
}

/* 
enum size = 4
 */