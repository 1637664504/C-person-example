#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

struct student{
    unsigned int number;
    char name[32];
    unsigned int age;
    unsigned int hight;
    struct list_head list;
};

int main()
{
    struct student s[10];
    char name[16][10]={"gg","jj","dd","mm","bb",
        "lili","Json","Luyisi","Adeland","Mali"};
    struct list_head list_stu;
    INIT_LIST_HEAD(&list_stu);
    int i;
    for(i=0;i<10;i++)
    {
        s[i].number = i+100;
        strcpy(s[i].name,name[i]);
        s[i].age = rand()%3+14;
        s[i].hight = rand()%20+150;
        list_add(&s[i].list, &list_stu);
    }

    struct student *tmp_stu;
    i=0;
    list_for_each_entry(tmp_stu,&list_stu,list)
    {
        printf("i=%d %u,%s,%u,%u\n",i++,tmp_stu->number,tmp_stu->name,tmp_stu->age,tmp_stu->hight);
    }

    return 0;
}
