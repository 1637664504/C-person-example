#include <stdio.h>

int main(int argc, char* const argv[])
{
    char *p;
    int i;
    for(i=0; argv[i]; i++ )
    {
        printf("i=%d %s\n",i,argv[i]);
    }
    return 0;
}