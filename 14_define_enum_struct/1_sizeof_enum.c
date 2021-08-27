
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum{
    eth_set_lan,
    eth_set_wan,
    eth_down,
}lan_eth_function_t;

int main ( int argc, char *argv[] )
{
    printf("enum size=%u",sizeof(lan_eth_function_t));

    return 0;
}