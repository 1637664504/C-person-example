#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "topic.h"

int main(int argc, char *argv[])
{
    struct list_head topic_list;
    struct topic *item;
    char name[4][32]={"test","demo","aaa","bbb"};
    int i=0;

    INIT_LIST_HEAD(&topic_list);
    assert(&topic_list);
    for(i=0;i<4;i++){
        item = malloc(sizeof(struct topic));
        assert(item);
        strcpy(item->topic_name,name[i]);
        list_add_tail(&item->list,&topic_list);
    }

    i=0;
    list_for_each_entry(item,&topic_list,list){
        printf("topic_name[%d]=%s\n",i++,item->topic_name);
    }

    return 0;
}