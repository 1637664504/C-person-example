/*
需求: 实现一个: 无序数组
1.数组: 3 1 2
2.Add 4: -- 3 1 2 4
   即添加到数组未
3.del 1：-- 3 4 2
   删除时，末尾补充。移动最少

特性:
    1.添加时，添加到末尾。
    2.删除时，末尾值替换，是数组只移动一个数。

解决问题：
1.网络主题访问，订阅者sock fd排序无意义。订阅者断开连接或退订主题时，浪费cpu 重排/移动sock fd
*/

//偷懒写法，不要参考,目的是让vscode F5 直接运行。 原版gcc 1_unorder_array_无序数组.c unorder_array.c -g -Wall -o xxx
//#include "unorder_array.h"
#include "unorder_array.c"

void test2(void)
{
	int num[]={5,1,3,4,2};
	struct unorder_array *a;
	struct unorder_array_opt opt;

	unorder_array_opt_init(&opt);
	opt.init(&a,16);
	opt.fill(a,num,5);
	opt.add(a,7);
	opt.del(a,3);
	opt.destory(a);
}

int main(void)
{
	int num[]={5,1,3,4,2};
	struct unorder_array *a;
	unorder_array_init(&a,16);
	unorder_array_fill(a,num,5);
	unorder_array_add(a,7);
	unorder_array_del(a,2);
	unorder_array_destory(a);

	test2();

	return 0;
}
