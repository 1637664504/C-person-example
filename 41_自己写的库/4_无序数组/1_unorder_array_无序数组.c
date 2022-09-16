/*
需求
1.数组: 3 1 2
2.Add 4: -- 3 1 2 4
   即添加到数组未
3.del 1：-- 3 4 2
   删除时，末尾补充。移动最少

解决问题：
1.网络主题访问，订阅者sock fd排序无意义。订阅者断开连接或退订主题时，浪费cpu 重排/移动sock fd
*/
#include <stdlib.h>

struct unorder_array{
	int size;
	int end;
	int capacity;
	int array[1024];
};

int unorder_array_init(struct unorder_array **a,int size)
{
	struct unorder_array *tmp;
	tmp = malloc(sizeof(struct unorder_array));
	if(tmp == NULL)
		return -1;
	tmp->size = 0;
	tmp->capacity = size;
	tmp->end = tmp->size - 1;
	*a = tmp;

	return 0;
}

void unorder_array_destory(struct unorder_array *a)
{
	if(a)
		free(a);
}

int unorder_array_fill(struct unorder_array *a,int *n,int len)
{
	if(a->size + len > a->capacity)
		return -1;
	int i;
	for(i=0;i<len;i++)
	{
		a->array[i] = *(n+i);
	}
	a->size = len;
	a->end = a->size - 1;


	return 0;
}

int unorder_array_add(struct unorder_array *a,int val)
{
	if(a->size+1 >= a->capacity)
		return -1;
	a->array[a->size] = val;
	a->size ++;
	a->end ++;

	return 0;
}

int unorder_array_find(struct unorder_array *a,int val)
{
	int size = a->size;
	int i;
	for(i=0;i<size;i++)
	{
		if(a->array[i] == val)
			return i;
	}

	return -1;
}

int unorder_array_del(struct unorder_array *a,int val)
{
	int idx = -1;
	idx = unorder_array_find(a,val);
	if(idx == -1)
		return -1;

	a->array[idx] = a->array[a->end];
	a->array[a->end] = 0;
	a->size --;
	a->end --;

	return 0;
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

	return 0;
}