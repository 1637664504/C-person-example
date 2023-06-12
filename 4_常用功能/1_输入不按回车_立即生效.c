#include <stdio.h>
#include <termios.h>

/* 终端输入立即生效 */
int config_input_nonlock(void)
{
    struct termios stored_settings;
    struct termios new_settings;

    tcgetattr(0, &stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_settings);
}

int main(void)
{
    int ret = 0;
    char c;
    config_input_nonlock();

    while(1)
    {
        c = getchar();
        putchar('\b'); // 删除回显
        printf("input:  [%c]\n", c);
        if(c == 'q')
            break;
        
    }

    return 0;
}