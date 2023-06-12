#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int main(int argc,char * argv[])
{

    struct timeval tv;
    while(1)
  {
          gettimeofday(&tv,NULL);
          printf("time %lu.%lu\n",tv.tv_sec,tv.tv_usec);
          sleep(2);
     }
    return 0;
}