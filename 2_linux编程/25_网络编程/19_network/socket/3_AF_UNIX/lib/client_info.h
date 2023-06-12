#ifndef _client_info_h_
#define _client_info_h_

struct client_info{
    int fd;

    //oem customer
};

struct client_manage{
    unsigned int count;
    unsigned int Max;
    unsigned int max_fd;
    struct client_info client[];
};

int client_manage_get_max_cleint_fd(struct client_manage *manage);
int client_manage_init(struct client_manage **manage, const unsigned int number);
int client_manage_free(struct client_manage *manage);
int client_manage_add(struct client_manage *manage,const int fd);
int client_manage_del(struct client_manage *manage,const int fd);
int client_manage_get_select_fd(struct client_manage *manage, fd_set *fds);
void client_manage_close_all(struct client_manage *manage);

#endif