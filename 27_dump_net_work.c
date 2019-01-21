#include	<stdlib.h>
#include    <stdio.h>
#include <arpa/inet.h>
#define MAX 32

void dump_network(unsigned char var[], int count)
{
    int i;
    int number=-16;

    for(i=0;i<count;i++)
    {
        if(i%16 == 0){
            printf("\n");
            printf("0x%2X ",number+=16);
        }
        printf("%2X ",var[i]);
    }
    printf("\n");
}

int main ( int argc, char *argv[] )
{
    unsigned char var[MAX];
    int i;

    for(i=0;i<MAX;i++){
        var[i]=i;
    }
    
    dump_network(var,MAX);
    
 return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */


