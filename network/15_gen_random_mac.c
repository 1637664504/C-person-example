#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int gen_random_mac(unsigned char *dst_mac)
{
    unsigned char mac[6];
    int i;
    if(!dst_mac)
    {
        return -1;
    }
    srand((unsigned int)time(NULL));
    for(i=0;i<6;i++){
        mac[i] = random()%0x100;
    }
    memcpy(dst_mac,mac,6);

    return 0;
}

int main ( int argc, char *argv[] )
{
    unsigned char mac[6];
    gen_random_mac(mac);
    printf("mac=%x:%x:%x-:%x:%x:%x\n",mac[0],mac[1],mac[2],
        mac[3],mac[4],mac[5]);

    return 0;
}

