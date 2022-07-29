/*
链表操作
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct ListNode {
 	int val;
 	struct ListNode *next;
 };

struct ListNode* list_reverse(struct ListNode* head)
{
    struct ListNode *now = head, *next=NULL, *last=NULL;
    while(now)
    {
        next = now->next;
        now->next = last;
        last = now;
        now = next;
    }

    //now is NULL;
    return last;
}

int list_add(struct ListNode** head,struct ListNode* t)
{
    if(!t)
        return -1;
    struct ListNode*p = *head;
    if(p == NULL)
    {
        *head = t;
    }
    else
    {
        while(p->next)
            p = p->next;

        p->next = t;
    }

    return 0;
}

void list_show(struct ListNode* head)
{
    if(head == NULL)
        return;

    struct ListNode*p = head;
    int i=0;

    while(p)
    {
        printf("i=%d,val=%d\n",i++,p->val);
        p=p->next;
    }
}

int main()
{
    struct ListNode *head=NULL,*t;
    int i;
    for(i=0;i<6;i++)
    {
        t = malloc(sizeof(struct ListNode));
        t->val=i;
        t->next=NULL;
        list_add(&head,t);
    }

    //2 list 遍历
    list_show(head);

    //3 list 反向
    struct ListNode *rever;
    rever = list_reverse(head);
    list_show(rever);
    return 0;
}