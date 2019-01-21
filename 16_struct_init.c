/* C语言不能对结构体进行, 预初始化
struct stu{
	int age=10;
	int name=12;
}

提示语法错误
*/

#include	<stdlib.h>
#include    <stdio.h>
struct stu {
    int age;
    int name;
};
int main ( int argc, char *argv[] )
{
  struct stu liuj;
    liuj.age=22;
    liuj.name=123;
    printf ( "\n" );
 return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

