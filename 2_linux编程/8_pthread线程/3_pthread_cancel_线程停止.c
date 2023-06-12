#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct thread_info{
    int age;
    char name[32];
};

void clean_fun(void *arg)
{
	char* s=(char*)arg;
	printf("clean_func: %s\n",s);
}

void *thread_handler(void *ptr)
{
    int execute = 1;
	pthread_cleanup_push(clean_fun, "first clean func\n");
	pthread_cleanup_push(clean_fun, "second clean func\n");
	printf("thread running %lx\n",pthread_self());
    sleep(3);
	pthread_cleanup_pop(execute);
	pthread_cleanup_pop(execute);

	return (void*)0;
}

int create_pthread(void)
{
    struct thread_info info;
    pthread_t pid;
    int ret;
    int *retval;

    ret = pthread_create(&pid,NULL,thread_handler,&info);
    if(ret)
        perror("pthread_create fail");
    pthread_detach(pid);
    sleep(1);
    pthread_cancel(pid);
}

int main ( int argc, char *argv[] )
{
    create_pthread();

    return 0;
}
