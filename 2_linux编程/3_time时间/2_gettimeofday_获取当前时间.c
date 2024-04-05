#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

double get_now_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

int main(int argc, char* argv[])
{
    double now_time;
	while (1) {
		now_time = get_now_time();
		printf("time %lf\n", now_time);
		sleep(2);
	}
	return 0;
}