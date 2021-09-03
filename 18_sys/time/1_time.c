#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main ( int argc, char *argv[] )
{
    time_t now, cur;

    now = time(NULL);
    sleep(2);
    cur = time(NULL);
    printf("%d - %d = %d \n",now,cur,cur-now);

    return 0;
}
/*
结论:
time(NULL) 返回时间，精度是 秒/s
*/