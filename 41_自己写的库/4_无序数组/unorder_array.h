#ifndef _unorder_array_h_
#define _unorder_array_h_

struct unorder_array{
	int size;
	int end;
	int capacity;
	int array[1024];
};
int unorder_array_init(struct unorder_array **a,int size);
void unorder_array_destory(struct unorder_array *a);
int unorder_array_fill(struct unorder_array *a,int *n,int len);
int unorder_array_add(struct unorder_array *a,int val);
int unorder_array_find(struct unorder_array *a,int val);
int unorder_array_del(struct unorder_array *a,int val);

struct unorder_array_opt{
	//struct unorder_array *a;
	int (*init)(struct unorder_array **a,int size);
	void (*destory)(struct unorder_array *a);
	int (*fill)(struct unorder_array *a,int *n,int len);
	int (*add)(struct unorder_array *a,int val);
	int (*del)(struct unorder_array *a,int val);
	int (*find)(struct unorder_array *a,int val);
};
int unorder_array_opt_init(struct unorder_array_opt *opt);

#endif