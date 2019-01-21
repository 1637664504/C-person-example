
#include	<stdlib.h>
#include    <stdio.h>

#define	EnableUSB 1		/*  */
#define	V1200_Enable_USB 0			/*  */

int main ( int argc, char *argv[] )
{
    #if (defined EnableUSB) && ( !defined V1200_Enable_USB)
    printf ( "111111111111\n" );
    #else
    printf ( "222222222222222\n" );
    #endif

 return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

