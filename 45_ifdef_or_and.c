#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//#define DMP_X_BROADCOM_COM_IPV6_1
#define DMP_X_BROADCOM_COM_IPV6_2

int main ( int argc, char *argv[] )
{
#if ((defined  DMP_X_BROADCOM_COM_IPV6_1) || (defined DMP_X_BROADCOM_COM_IPV6_2) )
    printf("11111111111\n");
#endif

#ifdef DMP_X_BROADCOM_COM_IPV6_1
    printf("22222222222\n");
#endif

    printf("-------------\n");
    return 0;
}
