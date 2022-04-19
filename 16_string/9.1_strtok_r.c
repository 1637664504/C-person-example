#include <stdio.h>
#include <string.h>

/*
测试分割字符
*/
void test1()
{
    char s[] = "ab-cd : ef;gh :i-jkl;mnop;qrs-tu: vwx-y;z";
    char *delim = "-";
    char *record = NULL;
    char *p;
    printf("%s \n", strtok_r(s, delim,&record));
    while((p = strtok_r(NULL, delim,&record)))
        printf("%s \n", p);

}
/*
测试1：
delime = "-"
ab
cd : ef;gh :i
jkl;mnop;qrs
tu: vwx-y;z

*/

int main(void)
{
    test1();

    return 0;
}
