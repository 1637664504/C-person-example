#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void *thread_handler(void *ptr)
{
    pid_t pid = getpid();
    pid_t ppid = getpid();


	return (void*)0;
}

int create_pthread(void)
{
    pthread_t pid;
    int ret;
    int *retval;


    ret = pthread_create(&pid,NULL,thread_handler,NULL);
    if(ret)
        perror("pthread_create fail");
    pthread_detach(pid);
    sleep(1);
}

int main ( int argc, char *argv[] )
{
    create_pthread();
    return 0;
}
