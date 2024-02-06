#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "class_A.h"

int main()
{
    // 栈-局部变量方式
    class_A a;
    class_A_init(&a,18,"lili");
    printf("a name=%s, age=%d\n", a.get_name(&a), a.get_age(&a));
    class_A_destroy(&a);

    // 堆-申请内存方式
    class_A* b = new_class_A(19, "Malike");
    if (b) {
        printf("b name=%s, age=%d\n", b->get_name(b), b->get_age(b));
        free_class_A(b);
    }

    return 0;
}