#include <stdio.h>
static unsigned int a=1;
unsigned int get_system_config_metric(unsigned int type)
{
    return a == type ? 10 : 20;
}
int main(void)
{
    unsigned int a = get_system_config_metric(0);
    printf("a=%d\n",a);

    return a;
}