

#include	<stdlib.h>
#include    <stdio.h>
#include <arpa/inet.h>
#define MAX 32
#define BCM_DIAG_24G_WIRELESS_CONN      19
#define BCM_DIAG_5G_WIRELESS_CONN      20

int main ( int argc, char *argv[] )
{
    printf("%d %d\n",BCM_DIAG_24G_WIRELESS_CONN,BCM_DIAG_5G_WIRELESS_CONN);
 
    
 return EXIT_SUCCESS;
}


