#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "topic.h"

struct topic *g_topic_start,*g_topic_end;

void topic_init()
{
    g_topic_start = NULL;
    g_topic_end = NULL;
}

struct topic *topic_add(const char *name)
{
    struct topic *tmp = NULL;

    tmp = malloc(sizeof(struct topic));
    if(tmp)
    {
        memset(tmp,0,sizeof(sizeof(struct topic)));
        strcpy(tmp->topic_name,name);

        if(g_topic_start == NULL)
            g_topic_start = tmp;
        if(g_topic_end)
            g_topic_end->next = tmp;

        g_topic_end = tmp;
    }
    return tmp;
}

struct topic * topic_search(const char *name)
{
    struct topic *tmp = NULL;
    int result = 0;

    if(!g_topic_start)
        return NULL;
    
    tmp = g_topic_start;
    for(; tmp; tmp=tmp->next){
        if(strncpy(tmp->topic_name,name,strlen(tmp->topic_name)))
            continue;
        else{
            result = 1;
            break;
        }
    }

    if(result == 0)
    {
        //tmp = topic_add(name);
        tmp = NULL;
    }

    return tmp;
}

void topic_del(struct topic *dst)
{
    struct topic *tmp = NULL;
    struct topic *last = NULL;
    if(!dst)
    {
        return;
    }

    for(tmp = g_topic_start; tmp; tmp=tmp->next)
    {
        if(strncmp(tmp->topic_name,dst->topic_name,strlen(tmp->topic_name)))
        {
            last = tmp;
            continue;
        }
        else
        {
            if(last)
            {
                if(tmp->next)
                {
                    last->next = tmp->next;
                }
                else                        //tmp is end [a]-[b]-[c]-[t]
                {
                    last->next = NULL;
                    g_topic_end = last;
                }
            }
            else if(g_topic_start == tmp)   //tmp is head [t]-[a]-[b]-[c]
            {
                if(g_topic_start->next)
                {
                    g_topic_start = tmp->next;
                }
                else                        //tmp is only [t]
                {
                    g_topic_start = NULL;
                    g_topic_end = NULL;
                }
            }

            free(tmp);
            tmp = NULL;
            break;
        }
    }
}

int topic_delete_one_topic(const char *name)
{
    struct topic *tmp = NULL;
    int ret = -1;
    if(!g_topic_start)
        return -1;

    for(tmp = g_topic_start; tmp; tmp=tmp->next){
        if(strncmp(tmp->topic_name,name,strlen(tmp->topic_name)))
            continue;
        else
        {
            topic_del(tmp);
            ret = 0;
            break;
        }
    }

    return ret;
}

void topic_show(void)
{
    struct topic *tmp = NULL;
    int i = 0;
    if(!g_topic_start)
    {
        printf("no any topic\n");
        return;
    }

    for(tmp = g_topic_start; tmp; tmp=tmp->next){
        printf("topic[%d]=%s\n",i++,tmp->topic_name);
    }
}

int main(int argc, char *argv[])
{
    char topic_demo[32] = "demo";
    struct topic *tmp;
    topic_init();

    tmp = topic_search(topic_demo);
    if(tmp == NULL)
        topic_add(topic_demo);
    topic_add("test");
    topic_add("aaa");
    topic_add("bbb");
    topic_show();
    printf("del test-------\n");
    topic_delete_one_topic("demo");
    //topic_delete_one_topic("test");
    topic_delete_one_topic("aaa");
    topic_delete_one_topic("bbb");
    topic_show();

    return 0;
}