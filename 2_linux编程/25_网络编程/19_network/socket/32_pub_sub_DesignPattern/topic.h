#ifndef _topic_h_
#define _topic_h_
#include "list.h"

#define TOPIC_MAX_SUB_CLIENT 64
struct topic{
    char topic_name[16];
    int sub_count;
    int sub_fd[TOPIC_MAX_SUB_CLIENT];
    struct topic *next;
    struct list_head list;
};

struct topic_manage{
    struct list_head list;
};

int topic_del_fd(struct topic_manage *manage, int fd);
int topic_add_fd(struct topic* item, int fd);
int topic_del(struct topic_manage *manage,const char* name);
struct topic* topic_search(struct topic_manage *manage,const char* name);
void topic_for_each_list_show(struct topic_manage *manage);
struct topic* topic_add(struct topic_manage *manage,const char* name);
struct topic* topic_add_tail(struct topic_manage *manage,const char* name);
int topic_manage_init(struct topic_manage *manage);

#endif