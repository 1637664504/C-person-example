/*
* =====================================================================================
*
*       Filename:  dup2.c
*
*    Description:
*
*        Version:  1.0
*        Created:  06/13/2018 07:09:08 PM
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
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main ( int argc, char *argv[] )
{
	char *p;
	p = getlogin();
	printf("%s\n",p);
 return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

