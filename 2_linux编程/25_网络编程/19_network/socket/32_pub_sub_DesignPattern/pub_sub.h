#ifndef _pub_sub_h_
#define _pub_sub_h_

#define TOPIC_PUB 1
#define TOPIC_SUB 2

/*
sub msg
    code=sub
    topic_name = "test"

pub msg
    code = pub
    tpoic_name = "test"
    info="hello world"
*/
struct sub_msg{
    unsigned char code;
    char topic_name[32];
};

struct pub_msg{
    unsigned char code;
    char topic_name[32];
    unsigned int len;
    void *info;
};

#endif