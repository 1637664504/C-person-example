#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct queue{
    char *p_buf;
    int len;
    char *p_start;
    char *p_end;
    char *p_now;
    //struct queue *this;
    void (*add)(struct queue *q,char *src);
    void (*show)(struct queue *q);
};

static void queue_add(struct queue *q,char *src);
static void queue_show(struct queue *q);

int queue_init(struct queue *q,unsigned int lenght)
{
    if(!q || !lenght)
        return -1;
    q->p_buf = malloc(lenght);
    if(!q->p_buf)
        return -1;
    memset(q->p_buf,0,lenght);
    q->len = lenght;
    q->p_start = q->p_buf;
    q->p_end = q->p_buf+lenght-1;
    q->p_now = q->p_start; 
    //this = q;
    q->add = queue_add;
    q->show = queue_show;

    return 0;
}

static void queue_add(struct queue *q,char *src)
{
    if(!q || !src)
        return;
    while(*src)
    {
        if(q->p_end <= q->p_now)
            q->p_now = q->p_start;
        *q->p_now++ = *src++;
    }
}

static void queue_show(struct queue *q)
{
    if(!q)
        return;
    printf("%s\n",q->p_start);
}

int main ( int argc, char *argv[] )
{
    struct queue q;
    queue_init(&q,16);
    q.add(&q,"123456789");
    q.add(&q,"aabbccddeeff");
    q.show(&q);
    return 0;
}

/*
测试: 字符缓冲队列

Result:
ddeeff789aabbcc
*/