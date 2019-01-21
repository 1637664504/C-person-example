/*
* =====================================================================================
*
*       Filename:  11_sprintf_2choose.c
*
*    Description:
*
*        Version:  1.0
*        Created:  06/29/2018 09:17:05 AM
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

int checkWanIsOnline(void)
{
    return 1;

}

int main ( int argc, char *argv[] )
{
    char varValue[64]={0};
//        if(checkWanIsOnline()){
//        sprintf(varValue, "%s,,,,,,", "up");
//
//        }else{
//            sprintf(varValue,"%s,,","down");
//        }

    sprintf(varValue,"%s,,",checkWanIsOnline()?"up":"down");
    printf ( "%s\n",varValue );
 return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

