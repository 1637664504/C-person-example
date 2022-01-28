#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef enum{
    INTERNET_RESULT_FAIL = -1,
    INTERNET_RESULT_OK,
}internet_result_e;

struct ping_option{
    char ifcname[16];
    char website[32];
    unsigned int count;
    unsigned int timeout;
};

struct ping_thread{
    struct ping_option opt;
    internet_result_e result;
    int score;
};

#define g_website_num 3
#define MAX_TRY_PING 3
//unsigned int g_website_num = 3;
char ping_website[g_website_num][32]={
    "8.8.8.8",
    "8.8.4.4",
    "223.5.5.5"
};

const unsigned int ping_timeout_list[MAX_TRY_PING]={4,8,8};

static int get_ping_result(const char *cmd)
{
    int ret;

    ret = system(cmd);
    printf("ret=%d cmd=%s\n",ret,cmd);

    return ret;
}

void* start_ping_thread(void *arg)
{
    if(arg == NULL)
        pthread_exit(NULL);

    char cmd[128] = "";
    struct ping_thread *thread = (struct ping_thread *)arg;
    int ret = INTERNET_RESULT_FAIL;

    snprintf(cmd,sizeof(cmd)-1,"ping -I %s -W %u -c %u %s",
        thread->opt.ifcname,
        thread->opt.timeout,
        thread->opt.count,
        thread->opt.website);

    ret = get_ping_result(cmd);
    if(ret == 0)
    {
        thread->score ++;
    }

    pthread_exit(thread);
}

unsigned int run_link_ping_thread(struct ping_option *opt)
{
    pthread_t pid[g_website_num];
    struct ping_thread thread[g_website_num] = {0};
    void *thread_exit;
    int i;
    int ret = -1;
    unsigned int score = 0;

    for(i=0; i<g_website_num; i++){
        strncpy(thread[i].opt.ifcname, opt->ifcname, sizeof(thread[i].opt.website)-1);
        strncpy(thread[i].opt.website, ping_website[i], sizeof(thread[i].opt.website)-1);
        thread[i].opt.timeout = opt->timeout;
        thread[i].opt.count = opt->count;

        ret = pthread_create(&pid[i],NULL,start_ping_thread,&thread[i]);
        if(ret)
        {
            perror("pthread_create fail");
            return 0;
        }
    }

    for(i=0; i<g_website_num; i++){
        pthread_join(pid[i],&thread_exit);
        score += thread[i].score;
    }

    return score;
}

int handler_internet_result(const char ifcname,unsigned int score)
{
    struct route_option opt;
    oem_fill_route_option(&opt,ifcname,score);
    set_default_route(&opt);
}

//Detect link network status
int detect_link_internet(const char* ifcname)
{
    unsigned int score = 0;
    unsigned int try_count;
    struct ping_option opt = {0};

    strncpy(opt.ifcname,ifcname,sizeof(opt.ifcname));
    opt.count = 3;

    for(try_count=0; try_count<MAX_TRY_PING; try_count++)
    {
        opt.timeout = ping_timeout_list[try_count];
        score = run_link_ping_thread(&opt);
        if(score > 0)
        {
            break;
        }
    }
    handler_internet_result(ifcname,score);
    
    return score;
}

void main_loop()
{
   char buf[256];
   char link[16];
   while(1)
   {
        memset(buf,0,sizeof(buf));
        //1.get event
        //fgets(buf, sizeof(buf)-1, stdin);
        scanf("%s",buf);
        if(strcmp(buf,"exit") == 0)
        {
            break;
        }

        if(strstr(buf,"eth"))
        {
            strncpy(link,buf,sizeof(link)-1);
            detect_link_internet(link);
        }
        else
            printf("unknow cmd\n");

   }
}

int main(int argc, char** argv)
{

    main_loop();
    
    return 0;
}