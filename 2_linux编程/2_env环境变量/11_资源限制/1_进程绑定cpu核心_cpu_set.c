#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define __USE_GNU
#include <sched.h>

int main()
{
    // 设置进程可以运行的 CPU 集合
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(2, &mask);

    // 设置进程的 CPU 亲和性
    sched_setaffinity(getpid(), sizeof(mask), &mask);

    // cpu压力测试
    uint64_t var;
    while (1) {
        if (var % 2 == 0) {
            var += 2;
        }
        else if (var % 3 == 0) {
            var *= 3;
        }
        else {
            var++;
        }
    }

    return 0;
}

/*
设置cpu 0时
    -- htop显示cpu1占用100%

设置cpu 1时
    -- htop显示cpu2占用100%

不绑定cpu 时
    -- htop显示在两个cpu之间切换
 */