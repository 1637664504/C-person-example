#include <stdio.h>
#include <string.h>

/*
测试分割字符
*/
void test1()
{
    char s[] = "ab-cd : ef;gh :i-jkl;mnop;qrs-tu: vwx-y;z";
    //char *delim = "-: ";
    char *delim = "-";
    char *p;
    printf("%s \n", strtok(s, delim));
    while((p = strtok(NULL, delim)))
        printf("%s \n", p);

}
/*
测试1：
delime = "-"
ab
cd : ef;gh :i
jkl;mnop;qrs
tu: vwx-y;z

测试2:
char *delim = "-: ";
ab
cd
ef;gh
...
*/

int main(void)
{
    test1();

    return 0;
}
