#include "list.h"
inline void
INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list->prev = list;
}

inline bool
list_empty(const struct list_head *head)
{
	return (head->next == head);
}

inline bool
list_is_first(const struct list_head *list,
	      const struct list_head *head)
{
	return list->prev == head;
}

inline bool
list_is_last(const struct list_head *list,
	     const struct list_head *head)
{
	return list->next == head;
}

inline void
_list_del(struct list_head *entry)
{
	entry->next->prev = entry->prev;
	entry->prev->next = entry->next;
}

inline void
list_del(struct list_head *entry)
{
	_list_del(entry);
	entry->next = entry->prev = NULL;
}

inline void
_list_add(struct list_head *_new, struct list_head *prev,
    struct list_head *next)
{

	next->prev = _new;
	_new->next = next;
	_new->prev = prev;
	prev->next = _new;
}

inline void
list_del_init(struct list_head *entry)
{
	_list_del(entry);
	INIT_LIST_HEAD(entry);
}

inline void
list_add(struct list_head *_new, struct list_head *head)
{
	_list_add(_new, head, head->next);
}

inline void
list_add_tail(struct list_head *_new, struct list_head *head)
{
	_list_add(_new, head->prev, head);
}

inline void
list_move(struct list_head *list, struct list_head *head)
{
	_list_del(list);
	list_add(list, head);
}

inline void
list_move_tail(struct list_head *entry, struct list_head *head)
{
	_list_del(entry);
	list_add_tail(entry, head);
}

inline void
_list_splice(const struct list_head *list, struct list_head *prev,
    struct list_head *next)
{
	struct list_head *first;
	struct list_head *last;

	if (list_empty(list))
		return;

	first = list->next;
	last = list->prev;
	first->prev = prev;
	prev->next = first;
	last->next = next;
	next->prev = last;
}

inline void
list_splice(const struct list_head *list, struct list_head *head)
{
	_list_splice(list, head, head->next);
}

inline void
list_splice_tail(struct list_head *list, struct list_head *head)
{
	_list_splice(list, head->prev, head);
}

inline void
list_splice_init(struct list_head *list, struct list_head *head)
{
	_list_splice(list, head, head->next);
	INIT_LIST_HEAD(list);
}

inline void
list_splice_tail_init(struct list_head *list, struct list_head *head)
{
	_list_splice(list, head->prev, head);
	INIT_LIST_HEAD(list);
}

