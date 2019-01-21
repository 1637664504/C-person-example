#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,const char *argv[])
{
    char buf[64]={0};
    char *p = buf;
    int len=0;
    time_t aabb;
    len = sprintf(p,"-w %d 111",123);
    p += len;

    sprintf(p,"-c %d",234);
    printf("%s\n",buf);
	return 0;
}

