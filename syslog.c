/*
* =====================================================================================
*
*       Filename:  syslog.c
*
*    Description:
*
*        Version:  1.0
*        Created:  06/12/2018 11:55:11 AM
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
#include <syslog.h>
#include <stdarg.h>

int main ( int argc, char *argv[] )
{
    openlog("liuj",LOG_PID|LOG_NDELAY,LOG_USER);
    syslog(LOG_NOTICE,"123456abcdef\n");
    closelog();
 return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

