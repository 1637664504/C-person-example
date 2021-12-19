#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "topic.h"

struct topic_manage{
    struct list_head list;
};

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
}