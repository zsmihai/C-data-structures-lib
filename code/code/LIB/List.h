

#ifndef _LIST_H_
#define _LIST_H_
struct LIST_NODE{
	int data;
	struct LIST_NODE* prev;
	struct LIST_NODE* next;
	
};

typedef struct LIST_NODE LIST_NODE;

typedef struct _LIST{
	LIST_NODE* first;
	LIST_NODE* last;
}LIST;

int list_create(LIST** list);


int list_insert(LIST* list, int element);

int list_merge(LIST* first_list, LIST* second_list, LIST** merged_list);

int list_merge_sort(LIST* list, LIST* sorted_list);

static int list_copy(LIST* old_list, LIST* new_list);

int list_deallocate(LIST** list);


#endif