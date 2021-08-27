/*
* =====================================================================================
*
*       Filename:  1_strtoul.c
*
*    Description:
*
*        Version:  1.0
*        Created:  06/21/2018 10:10:40 AM
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
#include <string.h>


int main ( int argc, char *argv[] )
{
	char str[]="16.31644.52370";
	u_int32_t valp;
	int base=0;
    char *ptr;

    valp = strtoul(str, &ptr, base);
    if (ptr == str) {
	printf("invalid numeric parameter '%s' for  option\n",
		     str);
	return 0;
    }
	printf("valp=%d,ptr=%s\n",
		     valp,ptr);
    return 1;
 return EXIT_SUCCESS;
}

