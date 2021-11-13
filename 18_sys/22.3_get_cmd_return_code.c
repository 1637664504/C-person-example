#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int system_cmd_call_get_exit_code(const char *cmd)
{
    int ret,status,finish,exit_code;

    ret = system(cmd);
    if(ret)
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


int main(void)
{
    //1.ret = 0, exit_code = 80
    //system_cmd_call_get_exit_code("ping 223.5.5.5 -I eth1 -W 8 -c 3");
    
    //2. ret=255
    //system_cmd_call_get_exit_code("ping 192.168.77.77 -W 8 -c 3");

    //3.
    //system_cmd_call_get_exit_code("./22.3_test1");
    system_cmd_call_get_exit_code("./22.3_test2");

    return 0;
}