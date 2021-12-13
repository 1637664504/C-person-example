#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "sys_thread.h"
int thread_manage_init(struct thread_manage *thread)
{
    int ret = 0;

    pthread_mutex_init(&thread->mutex, NULL);
    pthread_cond_init(&thread->cond, NULL);
    thread->state = thread_invalid;
    //pipe(thread->pipefd);
    ret = pipe2(thread->pipefd,O_NONBLOCK);

    return ret;
}

void thread_manage_release(struct thread_manage *thread)
{
    pthread_mutex_destroy(&thread->mutex);
    pthread_cond_destroy(&thread->cond);
    thread->state = thread_stop;
}

void thread_manage_suspend(struct thread_manage *thread, unsigned int wait_time)
{
    pthread_mutex_lock(&thread->mutex);

    thread->state = thread_stop;
    if(wait_time)
    {
        struct timespec tm = {0,0};
        tm.tv_sec = time(NULL) + wait_time;
        pthread_cond_timedwait(&thread->cond, &thread->mutex, &tm);
    }
    else
    {
        pthread_cond_wait(&thread->cond, &thread->mutex);
    }

    pthread_mutex_unlock(&thread->mutex);
}

void thread_manage_wait_wakeup(struct thread_manage *thread, unsigned int wait_time)
{
    pthread_mutex_lock(&thread->mutex);

    if(wait_time)
    {
        struct timespec tm = {0,0};
        tm.tv_sec = time(NULL) + wait_time;
        pthread_cond_timedwait(&thread->cond, &thread->mutex, &tm);
    }

    pthread_mutex_unlock(&thread->mutex);
}

void thread_manage_wakeup(struct thread_manage *thread)
{
    pthread_mutex_lock(&thread->mutex);
    thread->state = thread_running;
    pthread_cond_signal(&thread->cond);
    pthread_mutex_unlock(&thread->mutex);
}

void thread_manage_stop(struct thread_manage *thread)
{
    pthread_mutex_lock(&thread->mutex);
    thread->state = thread_stop;
    pthread_mutex_unlock(&thread->mutex);
}