#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

int system_cmd_call_get_exit_code(const char *cmd)
{
    int ret,status,finish,exit_code;

    ret = system(cmd);
    if(ret==0)
    {
        return 0;
    }
    else if(ret == -1)
    {
        return -1;
    }
    else
    {
        printf("ret=%d ,err=%s\n",ret,strerror(errno));
        if(WIFEXITED(status)){
            finish= WIFEXITED(status);
            exit_code = WEXITSTATUS(status);
            printf("cmd exit with %d. Finish=%d\n", exit_code,finish);
        }
        else if (WIFSIGNALED(status))
        {
                int if_finished_by_signal,signal_code;
                if_finished_by_signal = WIFSIGNALED(status);
                signal_code = WTERMSIG(status);
                printf( "signal_code is %d\n", signal_code);
        }
        else if (WIFSTOPPED(status))
        {
                int if_stoped,stop_signal_code;
                if_stoped = WIFSTOPPED(status);
                stop_signal_code = WSTOPSIG(status);
                printf( "stop_signal_code is %d\n", stop_signal_code);
        }
    }

    return ret;
}

int main(int argc, char *argv[])
{
    char cmd[256];
    int ret;

    sprintf(cmd,"ping www.baidu.com -I eth1 -W 8 -c 3");
    ret = system_cmd_call_get_exit_code(cmd);
    printf("ret=%d");

    return 0;
}