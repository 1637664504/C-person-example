#include <stdio.h>
#include <sys/resource.h>

int main(int argc, char** argv)
{
    const rlim_t kStackSize = 16 * 1024 * 1024; // min stack size = 64 Mb
    struct rlimit rl;
    int result;
    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        rl.rlim_cur = kStackSize;
        result = setrlimit(RLIMIT_STACK, &rl);
        if (result != 0)
        {
            fprintf(stderr, "setrlimit returned result = %d\n", result);
        }
    }
    return 0;
}
