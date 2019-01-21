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
    int fd;
    char buf[128]="12345567zbcdefg";

    fd = open("123.txt",O_RDWR|O_CREAT,666);
    dup2(fd,1);

    printf ( "1111111111\n" );
    write(fd,buf,strlen(buf));
    printf ( "222222222\n" );
 return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

