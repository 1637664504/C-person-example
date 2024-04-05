#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    char buf[64];
    int ret;
    ret = getlogin_r(buf, sizeof(buf));
    printf("11: login user: %s\n", buf);

    char* p;
    p = getlogin();
    printf("12: login user: %s\n", p);

    return 0;
}
