/*
* =====================================================================================
*
*       Filename:  26_htons.c
*
*    Description:
*
*        Version:  1.0
*        Created:  08/13/2018 08:16:25 PM
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
#include <arpa/inet.h>

int main ( int argc, char *argv[] )
{
    unsigned int ret;
    if(argc !=3){
        printf("Usage: %s <opt> [number]\n",argv[0]);
        printf("<opt> htonl htons ntohl ntohs\n");
        return 0;
    }

    if(strcmp(argv[1],"htons")){
        ret = htons(atoi(argv[2]));
        printf("%x %u\n",ret,ret);
    }else if(strcmp(argv[1],"htonl")){
        ret = htonl(atoi(argv[2]));
        printf("%x %u\n",ret,ret);
    }else if(strcmp(argv[1],"ntohl")){
        ret = ntohl(atoi(argv[2]));
        printf("%x %u\n",ret,ret);
    }else if(strcmp(argv[1],"ntohs")){
        ret = ntohs(atoi(argv[2]));
        printf("%x %u\n",ret,ret);
    }
 return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

