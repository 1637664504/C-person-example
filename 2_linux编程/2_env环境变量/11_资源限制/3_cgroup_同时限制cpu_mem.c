#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void test_cpu()
{
    printf("thread: test_cpu start\n");
    long long total = 0;
    while (1) {
        ++total;
        if (total > 2999999999)
            break;
    }
    printf("exit test cpu\n");
}

#define MEM_1M (1024*1024)
void* test_mem(void *arg)
{
    char* p = NULL;
    int size = 0;
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
}

int main()
{
    // pthread_t pid;
    // void *ret;
    // pthread_create(&pid, NULL, test_mem, NULL);
    // pthread_join(pid, &ret);
    // printf("test mem exit %d\n", *(int *)ret);

    test_cpu();
    test_mem(NULL);

    return 0;
}
