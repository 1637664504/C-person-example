/*
* =====================================================================================
*
*       Filename:  13_sleep_0.5s.c
*
*    Description:
*
*        Version:  1.0
*        Created:  07/11/2018 10:17:11 AM
*       Revision:  none
*       Compiler:  gcc
*
*         Author:  YOUR NAME (), 
*   Organization:  
*
* =====================================================================================
*/

#include	<stdlib.h>
#include    <stdio.h>

#include <unistd.h>
int main ( int argc, char *argv[] )
{

    int a;
    while(1)
    {
        sleep(1);

        printf ( "------------\n" );
    }
 return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

