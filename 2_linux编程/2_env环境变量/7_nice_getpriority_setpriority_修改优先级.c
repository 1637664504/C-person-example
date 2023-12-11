#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char* argv[])
{
    int cur_priority;

    // 1.修改前
    cur_priority = getpriority(PRIO_PROCESS, getpid());
    printf("before pri=%d\n", cur_priority);

    // 2.修改优先级之后
    setpriority(PRIO_PROCESS, getpid(), -10);
    cur_priority = getpriority(PRIO_PROCESS, getpid());
    printf("modify pri=%d\n", cur_priority);

    // 3.nice修改之后
    nice(-20);
    cur_priority = getpriority(PRIO_PROCESS, getpid());
    printf("nice pri=%d\n", cur_priority);

    return 0;
}

/*
before pri=0
modify pri=-10
nice pri=-20
*/