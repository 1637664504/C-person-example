
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define STRUCT_OFFSET(id, element) ((unsigned long)&((struct id*)0)->element)

struct stu{
    char name[16];
    int age;
    int id;
    char mac[16];
};

int main(int argc,char **argv)
{
    struct stu xi={"liuj",12,100,"45:67"};
    struct stu *mm;
    char *p = xi.mac;
    printf("xi=%p\n",&xi);
    mm =p-STRUCT_OFFSET(stu,mac);
    printf("mm=%p\n",mm);

    return 0;
}


