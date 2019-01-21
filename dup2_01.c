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
    int fd, fd_2;
    char buf[128]="12345567zbcdefg";

    fd = open("123.txt",O_RDWR|O_CREAT,666);
    fd_2 = open("234.txt",O_RDWR,666);
    dup2(fd_2,fd);


    char str_1[]="Hello,how are you\n";
    char str_2[]="Ye, I am very good\n";
    char str_3[]="Nice too meet you\n";
    write(fd,str_1,strlen(str_1));
    write(fd_2,str_2,strlen(str_2));
    write(fd,str_3,strlen(str_3));
 return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

