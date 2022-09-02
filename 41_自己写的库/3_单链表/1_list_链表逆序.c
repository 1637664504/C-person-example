#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


struct listNode{
	int val;
	struct listNode *next;
};

#if 0
//3个变量
void list_revert(struct listNode *head)
{
	struct listNode *now,*pre,*next;
	now = head;
	pre = NULL;
	next = NULL;
	while(now)
	{
		if(now->next)
		{
			next = now->next;
			now->next = pre;

			now = next;
			pre = now;
		}
		else
		{
			now->next = pre;
			break;
		}
	}
}
#endif

/*
链表 初始化
*/
int list_init(struct listNode **head,int a[],int len)
{
	struct listNode *now = NULL, *prev = NULL;

#ifdef way1	//方法1
	if(len)
	{
		now = malloc(sizeof(struct listNode));
		now->val = a[0];
		prev = now;
		*head = now;
	}
	else
	{
		return -1;
	}

	for(int i=1;i<len;i++)
	{
		now = malloc(sizeof(struct listNode));
		if(now)
		{
			//if(prev)
				prev->next = now;

			now->val = a[i];
			now->next = NULL;
			prev = now;
		}
		else{
			return -1;
		}
	}
#else		//方法2
	for(int i=0;i<len;i++)
	{
		now = malloc(sizeof(struct listNode));
		if(now)
		{
			if(prev)
				prev->next = now;

			now->val = a[i];
			now->next = NULL;
			prev = now;

			if(i==0)
			{
				*head = now;
			}
		}
		else{
			return -1;
		}
	}
#endif

	return 0;
}

/*
链表 逆序初始化
*/
int list_rinit(struct listNode **head,int a[],int len)
{
	struct listNode *new = NULL, *prev = NULL;
	for(int i=0;i<len;i++)
	{
		new = malloc(sizeof(struct listNode));
		if(new)
		{
			new->val = a[i];
			new->next = prev;
			prev = new;
		}
		else{
			return -1;
		}
	}

	*head = new;


	return 0;
}

/*
list 链表释放
单元测试:  valgrind --leak-check=full 检查通过
*/
void list_free(struct listNode *head)
{
	struct listNode *now = head;
	struct listNode *next;
	while(now)
	{
		if(now->next)
		{
			next=now->next;
			free(now);
			now=next;
		}
		else{
			free(now);
			now = NULL;
		}
	}
}

void list_show(struct listNode *head)
{
	struct listNode *now = head;
	while(now)
	{
		if(now->next)
		{
			printf("%d ",now->val);
			now=now->next;
		}
		else
		{
			printf("%d \n",now->val);
			now = NULL;
		}
	}
}

int main(void)
{
	int a[5]={1,2,3,4,5};
	struct listNode *head;
	//list_rinit(&head,a,5);
	list_init(&head,a,5);
	list_show(head);
	list_free(head);

	return 0;
}