#include <stdio.h>
#include <unistd.h>
#include <sys_thread.h>

void *test(void *arg)
{
    struct thread_manage *mg = arg;

    thread_manage_stop(mg);
    while(1)
    {
        if(mg->state == thread_stop)
        {
            printf("%s:%d]suspend\n",__func__,__LINE__ );
            mg->suspend(mg,0);
            printf("%s:%d]wakeup\n",__func__,__LINE__ );
            continue;
        }
        printf("%s:%d]runing\n",__func__,__LINE__);
        mg->suspend(mg,5);
    }
}

void getcmd(struct thread_manage *mg)
{
    char cmd[32];
    while(1)
    {
        scanf("%s\n",cmd);
        if(cmd[0]=='e')
            return;

        if(cmd[0] == 'r')
        {
            //set_run
            mg->run(mg);
        }
        else if(cmd[0] == 's')
        {
            //set_stop
            mg->stop(mg);
        }
    }
}

int main(int argc,const char *argv[])
{
    printf("111\n");
    struct thread_manage mg;
    thread_manage_init(&mg);

    pthread_t tid;
    int ret = pthread_create(&tid,NULL,test,&mg);
    if(ret)
        perror("create thread fail:");

    getcmd(&mg);

    thread_manage_destroy(&mg);
    return 0;
}

