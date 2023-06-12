#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main ( int argc, char *argv[] )
{
    int ret = 0;
    ret = access("test.txt",F_OK);

    return 0;
}
/*

*/