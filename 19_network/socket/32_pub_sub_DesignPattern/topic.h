#ifndef _topic_h_
#define _topic_h_
#include "list.h"

struct topic{
    char topic_name[16];
    int sub_count;
    //int sub_fd[64];
    struct topic *next;
    struct list_head list;
};

#endif