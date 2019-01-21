#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

void bt(void)
{
    #define MAX_DEPTH (20)
    void *buffer[MAX_DEPTH];
    int nptrs = backtrace(buffer, MAX_DEPTH);
    char **stack = backtrace_symbols(buffer, nptrs);
    int i;
    
    if (stack)
    {
        for (i = 0; i < nptrs; ++i)
        {
            printf("%s\n", stack[i]);
        }
        
        free(stack);
    }

    return;
}

static void func2(void)
{
    bt(); 
}

inline void func1(void)
{
    func2();
}

void func(void)
{
    func1();
}

int main(int argc, char *argv[])
{
    func();
    
    return 0;
}

