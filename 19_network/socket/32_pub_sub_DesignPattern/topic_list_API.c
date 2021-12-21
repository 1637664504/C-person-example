#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "topic.h"

int topic_manage_init(struct topic_manage *manage)
{
    int ret = -1;
    //manage = malloc(sizeof(struct topic_manage));
    if(manage)
    {
        memset(manage,0,sizeof(struct topic_manage));
        INIT_LIST_HEAD(&manage->list);
        ret = 0;
    }

    return ret;
}

struct topic* topic_add_tail(struct topic_manage *manage,const char* name)
{
    struct topic *item = NULL;

    if(!name || name[0]=='\0')
        return NULL;

    item=malloc(sizeof(*item));
    if(item)
    {
        strcpy(item->topic_name,name);
        list_add_tail(&item->list, &manage->list);
    }

    return item;
}

struct topic* topic_add(struct topic_manage *manage,const char* name)
{
    struct topic *item = NULL;

    if(!name || name[0]=='\0')
        return NULL;

    item=malloc(sizeof(*item));
    if(item)
    {
        strcpy(item->topic_name,name);
        list_add(&item->list, &manage->list);
    }

    return item;
}

int topic_add_fd(struct topic* item, int fd)
{
    int i;
    for(i=0;i<TOPIC_MAX_SUB_CLIENT;i++)
    {
        if(item->sub_fd[i] == 0)
        {
            item->sub_fd[i] = fd;
            item->sub_count ++;
        }
    }
}

int topic_del_fd(struct topic_manage *manage, int fd)
{
    struct topic *item = NULL;
    int i;
    

    if(!manage && !fd)
        return ;

    list_for_each_entry(item,&manage->list,list){
        for(i=0; i<TOPIC_MAX_SUB_CLIENT; i++)
        {
            if(item->sub_fd[i] == fd)
            {
                item->sub_fd[i] == 0;
                item->sub_count --;
                return 0;
            }
        }
    }

    return -1;
}

int topic_del(struct topic_manage *manage,const char* name)
{
    struct topic *item = NULL;

    if(!name || name[0]=='\0')
        return NULL;

    list_for_each_entry(item,&manage->list,list){
        if(strncmp(item->topic_name,name,strlen(item->topic_name)))
            continue;
        else
        {
            list_del(&item->list);
            free(item);
            break;
        }
    }

    return item;
}

struct topic* topic_search(struct topic_manage *manage,const char* name)
{
    struct topic *item = NULL;

    if(!name || name[0]=='\0')
        return NULL;

    list_for_each_entry(item,&manage->list,list){
        if(strncmp(item->topic_name,name,strlen(item->topic_name)))
            continue;
        else
        {
            break;
        }
    }

    return item;
}


void topic_for_each_list_show(struct topic_manage *manage)
{
    struct topic *item;
    int i=0;
    list_for_each_entry(item,&manage->list,list){
        printf("topic_name[%d]=%s\n",i++,item->topic_name);
    }
}

#if TEST
int main(int argc, char *argv[])
{
    struct topic_manage manage;
    topic_manage_init(&manage);
    char name[4][32]={"test","demo","aaa","bbb"};
    int i=0;

    for(i=0;i<4;i++){
        topic_add(&manage,name[i]);
    }
    topic_for_each_list_show(&manage);

    for(i=0;i<4;i++){
        topic_del_one(&manage,name[i]);
    }
    topic_for_each_list_show(&manage);

    return 0;
}#endif
