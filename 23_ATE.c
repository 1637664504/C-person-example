/*
* =====================================================================================
*
*       Filename:  23_ATE.c
*
*    Description:
*
*        Version:  1.0
*        Created:  08/07/2018 01:52:44 PM
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

#define	ATE_MAGIC ('A'<<24|'T'<<16|'E'<<8)			/*  */
int main ( int argc, char *argv[] )
{
    unsigned int var=0;
    unsigned char a='A',b='T',c='E';
    var= a<<24 | b<<16 | c<<8;

    printf ( "var=0x%X\n",var );

    printf ( "ATE=0x%X\n",ATE_MAGIC );
 return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

