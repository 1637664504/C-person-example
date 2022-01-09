#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "client_info.h"

int client_manage_get_max_cleint_fd(struct client_manage *manage)
{
    int i = manage->Max - 1;
    int max_fd = manage->client[i].fd;

    for(i-- ; i>=0 ; i--){
        if(max_fd < manage->client[i].fd)
            max_fd = manage->client[i].fd;
    }

    return max_fd;
}

int client_manage_init(struct client_manage **manage, const unsigned int number)
{
    int ret = -1;

    if(number == 0 || manage == NULL)
        return -1;

    *manage = malloc(sizeof(struct client_manage) + sizeof(struct client_info)*number);
    if(*manage)
    {
        (*manage)->count = 0;
        (*manage)->Max = number;
        (*manage)->max_fd = 0;
        ret = 0;
    }

    return ret;
}

int client_manage_free(struct client_manage *manage)
{
    int ret = -1;

    if(manage == NULL)
        return -1;

    free(manage);
    manage = NULL;

    return ret;
}

int client_manage_add(struct client_manage *manage,const int fd)
{
    int ret = -1;
    int i;

    if(manage->count == manage->Max)
        return -1;

    for(i=0;i<manage->Max;i++)
    {
        if(manage->client[i].fd == 0)
        {
            manage->client[i].fd = fd;
            ret = 0;

            manage->count++;
            if(fd > manage->max_fd)
                manage->max_fd = fd;

            break;
        }
    }

    return ret;
}

int client_manage_del(struct client_manage *manage,const int fd)
{
    int ret = -1;
    int i;

    if(manage->count == 0)
        return -1;

    for(i=0;i<manage->Max;i++)
    {
        if(manage->client[i].fd == fd)
        {
            manage->client[i].fd = 0;
            ret = 0;

            manage->count--;
            if(manage->max_fd == fd)
                manage->max_fd = client_manage_get_max_cleint_fd(manage);
                
            break;
        }
    }

    return ret;
}

int client_manage_get_select_fd(struct client_manage *manage, fd_set *fds)
{
    int set_fd = 0;
    int i;

    if(manage->count == 0)
        return -1;

    for(i=0;i<manage->Max;i++)
    {
        if(FD_ISSET(manage->client[i].fd,fds))
        {
            set_fd = manage->client[i].fd;
            break;
        }
    }

    return set_fd;
}

void client_manage_close_all(struct client_manage *manage)
{
    int i;

    if(manage->count == 0)
        return ;

    for(i=0;i<manage->Max;i++)
    {
        if(manage->client[i].fd)
        {
            close(manage->client[i].fd);
        }
    }

    return ;
}

#if UNIT_TEST
int main()
{
    struct client_manage *tmp = NULL;
    client_manage_init(&tmp,10);

    int i;
    for(i=0;i<tmp->Max;i++){
        //tmp->client[i].fd = i;
        client_manage_add(tmp,i);
    }

    client_manage_del(tmp,9);
    int max_fd = client_manage_get_max_cleint_fd(tmp);
    printf("max_fd=%d \n",max_fd);
    
    for(i=0;i<tmp->Max;i++){
        printf("%d: fd=%d \n",i,tmp->client[i].fd);
    }

    client_manage_free(tmp);

    return 0;
}
#endif