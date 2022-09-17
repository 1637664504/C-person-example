#include <stdlib.h>
#include "unorder_array.h"

int unorder_array_opt_init(struct unorder_array_opt *opt)
{
	//opt->a = array;
	opt->init = unorder_array_init;
	opt->destory = unorder_array_destory;
	opt->fill = unorder_array_fill;
	opt->add = unorder_array_add;
	opt->del = unorder_array_del;
	opt->find = unorder_array_find;

	return 0;
}

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