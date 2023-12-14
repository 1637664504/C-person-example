#include <stdio.h>
#define __USE_GNU
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char** ep;
    for (ep = environ; *ep; ep++) {
        printf("%s\n", *ep);
    }

    return 0;
}
