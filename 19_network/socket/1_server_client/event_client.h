#ifndef _event_client_h_
#define _event_client_h_

#include "event.h"

struct event_client{
    event_program program;
    unsigned int event_fd;
};
int register_event(enum event_program program);
int send_event(const int sock,enum event_program program,const void *info,const unsigned int info_len);

#endif