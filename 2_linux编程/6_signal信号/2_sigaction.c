
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void handler_signal(int signal)
{
    printf("sig=%d \n",signal);
}

int main ( int argc, char *argv[] )
{
    struct sigaction act;
    act.sa_handler = handler_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT,&act,0);

    while(1){
        printf("main ------+++++\n");
        sleep(1);
    }

    return 0;
}