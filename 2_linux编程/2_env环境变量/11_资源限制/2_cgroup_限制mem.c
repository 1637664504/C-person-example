#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MEM_1M (1024*1024)

int main()
{
    int size = 0;
    char* p = NULL;
    while (1)
    {
        if ((p = (char*)malloc(MEM_1M)) == NULL)
        {
            break;
        }
        memset(p, 0, MEM_1M);
        printf("[%u]-- [%d]MB is allocated\n", getpid(), ++size);
        sleep(1);
    }

    return 0;
}
