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
    pid_t pid;
    //pid_t ppid;
    pthread_t thread_pid;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    //int pipefd[2];
    THREAD_STATE state;
    void (*fun)(void *arg);

    void (*init)(struct thread_manage *thread, void(*thead_fun)(void *arg));
    void (*run)(struct thread_manage *thread);
    void (*stop)(struct thread_manage *thread);
    void (*suspend)(struct thread_manage *thread, unsigned int wait_time);
    void (*wakeup)(struct thread_manage *thread, unsigned int wait_time);

    //to do
    //void (*sync_stop)(struct thread_manage *thread);
    //void (*sync_suspend)(struct thread_manage *thread, unsigned int wait_time);
};

int thread_manage_init(struct thread_manage *thread, void(*thead_fun)(void *arg));
void thread_manage_destroy(struct thread_manage *thread);

void thread_manage_suspend(struct thread_manage *thread, unsigned int wait_time);
void thread_manage_wakeup(struct thread_manage *thread, unsigned int wait_time);
void thread_manage_run(struct thread_manage *thread);
void thread_manage_stop(struct thread_manage *thread);

#endif

