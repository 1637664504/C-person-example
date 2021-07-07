#include <signal.h>
#include <stdio.h>

//2.signal 信号回调函数
void handler_signal_term(int signal_num)
{
    printf("signal=%d\n",signal_num);
}

int main ( int argc, char *argv[] )
{
    //1.捕捉signal 15 term信号, 注册回调函数
    signal(SIGTERM,handler_signal_term);

    getc(stdin);
    return 0;
}

