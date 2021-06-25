/*


*/

#include    <stdio.h>
#include	<stdlib.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char buf[64]="123456";
    char *p=NULL;
    p=strchr(buf,',');
    printf("p=%s\n",p);

    char buf1[64]="789";
    strncat(buf,buf1,64);
    printf("buf=%s\n",buf);

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */


