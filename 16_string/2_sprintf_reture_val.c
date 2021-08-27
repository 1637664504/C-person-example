/*
* =====================================================================================
*
*       Filename:  2_sprintf_reture_val.c
*
*    Description:
*
*        Version:  1.0
*        Created:  07/04/2018 09:23:10 AM
*       Revision:  none
*       Compiler:  gcc
*
*         Author:  YOUR NAME (), 
*   Organization:  
*
* =====================================================================================
*/

#include    <stdio.h>
#include	<stdlib.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char buf[64]={0};
    int ret;
    ret = sprintf(buf,"123 %d %s\n",555,"liuj");
    printf("ret =%d, buf=%s, len=%d \n",ret,buf,strlen(buf));
 return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

