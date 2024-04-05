#include <assert.h>
#include <stdio.h>
// 1.数值比较
void assert_num()
{
    int a = 5;

    assert(a == 5);
    printf("a == 5 :true\n");

    assert(a > 5);
    printf("a > 5 :true\n");
}

// 2.指针为NULL 断言
void assert_point()
{
    int a = 2;
    int *p = &a;
    assert(p);
    printf("p has point: true\n");

    p = NULL;
    assert(p);
    printf("p is null: true\n");
}

int main()
{
    // assert_num();    //比较大小
    assert_point();     //指针判断

    return 0;
}