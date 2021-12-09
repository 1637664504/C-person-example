#ifndef _sys_thread_h
#define _sys_thread_h

#include <pthread.h>
#include <time.h>

typedef enum{
    thread_invalid = 0,
    thread_stop,
    thread_running,
}THREAD_STATE;

struct thread_manage{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int cmd;
    THREAD_STATE state;
};

void thread_manage_stop(struct thread_manage *thread);
void thread_manage_wakeup(struct thread_manage *thread);
void thread_manage_suspend(struct thread_manage *thread, unsigned int wait_time);
void thread_manage_wait(struct thread_manage *thread, unsigned int wait_time);
void thread_manage_release(struct thread_manage *thread);
int thread_manage_init(struct thread_manage *thread);

#endif