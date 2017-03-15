#include<stdlib.h>
#include"List.h"
#include"Status.h"
int list_init(LIST* list);

int list_create(LIST** list){

	int status;
	LIST* new_list;

	status = EXIT_SUCCESS;
	new_list = NULL;


	if (NULL == list)
	{
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	new_list = (LIST*)malloc(sizeof(LIST) );


	if (NULL == new_list)
	{
		status = STATUS_MALLOC_FAIL;
		goto CleanUp;
	}

	status = list_init(new_list);

	if (status != EXIT_SUCCESS)
	{
		goto CleanUp;
	}

	*list = new_list;

CleanUp:

	if (status != EXIT_SUCCESS)
	{
		if (NULL != new_list){
			list_deallocate(&new_list);
		}
	}

	return status;
}

int list_init(LIST* list){

	int status;

	status = EXIT_SUCCESS;

	if (NULL == list){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	list->first = NULL;
	list->last = NULL;



CleanUp:
	return status;
}


int list_insert(LIST *list, int element){

	int status;
	LIST_NODE* node;


	node = NULL;
	status = EXIT_SUCCESS;

	if (NULL == list){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}


	node = (LIST_NODE*)malloc(sizeof(LIST_NODE));

	if (NULL == node){
		status = STATUS_MALLOC_FAIL;
		goto CleanUp;
	}


	node->data = element;
	if (list->first == NULL){
		list->first = node;
		list->last = node;
		node->prev = NULL;
		node->next = NULL;
	}
	else{
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
		node->next = NULL;
	}

CleanUp:
	return status;
}


static void list_append(LIST* list, LIST_NODE* node){

	if (NULL == list || NULL == node)
		return;

	if (list->last == NULL){
		list->first = node;
		list->last = node;
		node->prev = NULL;
		node->next = NULL;
	}
	else{
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
		
		node->next = NULL;
	}


}


int list_merge(LIST* first_list, LIST* second_list, LIST** merged_list){

	int status;
	LIST* new_list;
	LIST_NODE* current_first;
	LIST_NODE* current_second;


	new_list = NULL;
	current_first = NULL;
	current_second = NULL;

	status = EXIT_SUCCESS;

	if (NULL == first_list)
	{
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	if (NULL == second_list)
	{
		status = STATUS_INVALID_PARAMETER_2;
		goto CleanUp;
	}

	if (NULL == merged_list)
	{
		status = STATUS_INVALID_PARAMETER_3;
		goto CleanUp;
	}

	status = list_create(&new_list);

	if (status != EXIT_SUCCESS){
		goto CleanUp;
	}


	current_first = first_list->first;
	current_second = second_list->first;

	while (current_first != NULL && current_second != NULL)
	{

		if (current_first->data < current_second->data)
		{
			status = list_insert(new_list, current_first->data);
			if (status != EXIT_SUCCESS)
			{
				goto CleanUp;
			}
			current_first = current_first->next;
		}
		else
		{
			status = list_insert(new_list, current_second->data);
			if (status != EXIT_SUCCESS)
			{
				goto CleanUp;
			}
			current_second = current_second->next;
		}
	}
	while (current_first != NULL){

		status = list_insert(new_list, current_first->data);
		if (status != EXIT_SUCCESS)
		{
			goto CleanUp;
		}
		current_first = current_first->next;
	}
	while (current_second != NULL){
		status = list_insert(new_list, current_second->data);
		if (status != EXIT_SUCCESS)
		{
			goto CleanUp;
		}
		current_second = current_second->next;

	}


	*merged_list = new_list;

CleanUp:

	if (status != EXIT_SUCCESS){

		if (new_list != NULL)
			list_deallocate(&new_list);
	}
	return status;
}



static void list_merge_in_place(LIST* first_list, LIST* second_list, LIST* merged_list){

	LIST_NODE* current_first;
	LIST_NODE* current_second;
	LIST_NODE* next_node;
	//null
	next_node = NULL;
	current_first = first_list->first;
	current_second = second_list->first;

	while (current_first != NULL && current_second != NULL)
	{

		if (current_first->data < current_second->data)
		{
			next_node = current_first->next;
			list_append(merged_list, current_first);
			current_first = next_node;
			
		}
		else
		{
			next_node = current_second->next;
			list_append(merged_list, current_second);
			current_second=next_node;
		}
	}
	while (current_first != NULL){

		next_node = current_first->next;
		list_append(merged_list, current_first);
		current_first =next_node;
	}
	while (current_second != NULL){
		next_node = current_second->next;
		list_append(merged_list, current_second);
		current_second = next_node;

	}
}


static void list_get_next_len(LIST_NODE* start, int len, LIST* list, LIST_NODE** next_node){

	LIST_NODE* current_node;
	LIST_NODE* prev;

	prev = NULL;

	current_node = start;

	while (current_node != NULL && len>0){
		prev = current_node;
		current_node = current_node->next;
		len--;
	}
	
	list->first = start;
	list->last = prev;
	if (NULL!=prev)
	prev->next = NULL;

	*next_node = current_node;
}

static void list_join(LIST* first_list, LIST* second_list){


	if (first_list->last == NULL){
		first_list->first = second_list->first;
		first_list->last = second_list->last;
	}
	else{
		first_list->last->next = second_list->first;
		second_list->first->prev = first_list->last;
		first_list->last = second_list->last;
	}


}


void list_length(LIST* list, int* len){
	LIST_NODE* current_node;
	int length;

	current_node = list->first;
	length = 0;

	while (NULL != current_node){
		current_node = current_node->next;
		length++;
	}

	*len = length;
}

int list_merge_sort(LIST* list, LIST* sorted_list){
	int status;
	int len;
	LIST first_list, second_list;
	LIST_NODE* prev_last;
	LIST_NODE* current_node;
	LIST new_list;
	LIST merged_sublist;
	int list_len;

	status = EXIT_SUCCESS;
	prev_last = NULL;
	current_node = NULL;
	list_len = 0;

	if (NULL == list){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}


	if (NULL == sorted_list){
		status = STATUS_INVALID_PARAMETER_2;
		goto CleanUp;
	}


	//TODO validate

	status = list_copy(list, sorted_list);

	if (status != EXIT_SUCCESS){
		goto CleanUp;
	}
	
	len = 1;


	list_length(list, &list_len);

	while ( len <list_len ){		
		current_node = sorted_list->first;
		list_init(&new_list);
	
		while (NULL!=current_node){
			list_init(&first_list);
			list_get_next_len(current_node, len, &first_list, &current_node);
			
			list_init(&second_list);
			list_get_next_len(current_node, len, &second_list, &current_node);

			list_init(&merged_sublist);
			list_merge_in_place(&first_list, &second_list, &merged_sublist);

			list_join(&new_list, &merged_sublist);

		}
		sorted_list->first = new_list.first;
		sorted_list->last = new_list.last;
		len *= 2;
	}


CleanUp:
	return status;
}


static int list_copy(LIST* old_list, LIST* new_list){
	int status;
	LIST_NODE* current_node;

	status = EXIT_SUCCESS;
	current_node = NULL;

	status = list_init(new_list);

	if (status != EXIT_SUCCESS)
		goto CleanUp;

	current_node = old_list->first;

	while (NULL != current_node){
		status = list_insert(new_list, current_node->data);
		if (status != EXIT_SUCCESS)
			goto CleanUp;
		current_node = current_node->next;
	}

CleanUp:
	return status;
	
}


int list_deallocate(LIST** list){

	int status;
	LIST_NODE* current_node, *next_node;
	status = EXIT_SUCCESS;
	current_node = NULL;
	next_node = NULL;

	if (NULL == list){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	current_node = (*list)->first;
	while (current_node != NULL){
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
	
	(*list)->first = NULL;
	(*list)->last = NULL;

	free(*list);
	*list = NULL;
CleanUp:
	return status;
}