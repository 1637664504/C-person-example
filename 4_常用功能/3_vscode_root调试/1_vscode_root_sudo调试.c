#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    char cmd[] = "sudo ls /";
    system(cmd);

    return 0;
}
