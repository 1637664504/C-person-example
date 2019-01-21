/*
* =====================================================================================
*
*       Filename:  12_struct.c
*
*    Description:
*
*        Version:  1.0
*        Created:  07/06/2018 10:03:57 AM
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
static struct cgiSecInfo {
        int TotalNum;
        int TotalTrigPort;
        int TotalOpenPort;
} SecInfo;

int main ( int argc, char *argv[] )
{
    SecInfo.TotalNum=1;
    printf ( "%d\n",SecInfo.TotalOpenPort );
 return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

