#include"Heap.h"
#include"Status.h"
#include<stdlib.h>

int heap_init(HEAP* heap, int(*comp)(int, int));

int heap_create(HEAP** heap, int(*comp)(int, int))
{
	int status;
	HEAP* new_heap;

	status = EXIT_SUCCESS;
	new_heap = NULL;

	if (NULL == heap){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	new_heap = (HEAP*)malloc(sizeof(HEAP));

	if (NULL == new_heap){
		status = STATUS_MALLOC_FAIL;
		goto CleanUp;
	}

	status = heap_init(new_heap, comp);
	if (status != EXIT_SUCCESS){
		goto CleanUp;
	}

	*heap = new_heap;

CleanUp:
	if (status != EXIT_SUCCESS){
		if (new_heap != NULL)
			heap_deallocate(&new_heap);
		*heap = NULL;
	}
	return status;
}

int heap_init(HEAP* heap, int(*comp)(int, int)){
	int status;

	status = EXIT_SUCCESS;

	if (NULL == heap){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	if (NULL == comp){
		status = STATUS_INVALID_PARAMETER_2;
		goto CleanUp;
	}

	status = vector_create(&(heap->v));

	if (status != EXIT_SUCCESS){
		goto CleanUp;
	}

	heap->comp = comp;


CleanUp:

	return status;
}


static int heap_swap(HEAP* heap, int position1, int position2){

	int status;
	int el1, el2;

	status = 0;
	el1 = el2 = 0;

	status = vector_at((heap->v), position1, &el1);
	if (status != EXIT_SUCCESS)
	{
		goto CleanUp;
	}

	status = vector_at((heap->v), position2, &el2);
	if (status != EXIT_SUCCESS)
	{
		goto CleanUp;
	}

	status = vector_insert_by_position((heap->v), el1, position2);
	if (status != EXIT_SUCCESS)
	{
		goto CleanUp;
	}

	status = vector_insert_by_position((heap->v), el2, position1);
	if (status != EXIT_SUCCESS)
	{
		goto CleanUp;
	}


CleanUp:
	return status;

}



int heap_min_heap_comp(int el1, int el2){
	if (el2 > el1)
		return 1;
	else if (el2 == el1)
		return 0;
	else
		return -1;
}


int heap_max_heap_comp(int el1, int el2){
	if (el2 < el1)
		return 1;
	else if (el2 == el1)
		return 0;
	else
		return -1;
}

int heap_push(HEAP* heap, int element){

	int status;
	int current_pos;

	current_pos = -1;

	status = EXIT_SUCCESS;

	if (NULL == heap){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	if (!heap_initialized(heap)){
		status = STATUS_NOT_INITIALIZED;
		goto CleanUp;
	}


	status = vector_insert(heap->v, element);

	if (status != EXIT_SUCCESS){
		goto CleanUp;
	}

	current_pos = heap->v->size - 1;

	while (current_pos > 0 &&
			heap->comp(heap->v->elems[PARENT(current_pos)], heap->v->elems[current_pos]) == -1)
	{
		heap_swap(heap, PARENT(current_pos), PARENT(current_pos));
		
		current_pos = PARENT(current_pos);
	}



CleanUp:

	return status;
}

int heap_top(HEAP* heap, int* element){
	int status;
	int val;

	val = 0;
	status = EXIT_SUCCESS;

	if (NULL == heap){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	if (NULL == element){
		status = STATUS_INVALID_PARAMETER_2;
		goto CleanUp;
	}

	if (!heap_initialized(heap)){
		status = STATUS_NOT_INITIALIZED;
		goto CleanUp;
	}

	status = vector_at(heap->v, 0, element);

CleanUp:
	return status;
}

int heap_pop(HEAP* heap){
	int status;
	int last_element;
	int largest;
	int current_pos;
	int left_element;
	int right_element;
	int current_element;
	int heap_size;
	int changed;

	status = EXIT_SUCCESS;
	last_element = 0;
	largest = 0;
	current_pos = 0;
	left_element = 0;
	right_element = 0;
	current_element = 0;
	heap_size = 0;
	changed = 0;

	if (NULL == heap){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	if (!heap_initialized(heap)){
		status = STATUS_NOT_INITIALIZED;
		goto CleanUp;
	}


	status = vector_size((heap->v), &heap_size);
	if (status != EXIT_SUCCESS){
		goto CleanUp;
	}

	status = vector_at((heap->v), heap_size - 1, &last_element);
	if (status != EXIT_SUCCESS){
		goto CleanUp;
	}

	status = vector_insert_by_position((heap->v), last_element, 0);
	if (status != EXIT_SUCCESS){
		goto CleanUp;
	}

	status = vector_remove_by_position((heap->v), heap_size - 1);
	if (status != EXIT_SUCCESS){
		goto CleanUp;
	}


	status = vector_size((heap->v), &heap_size);
	if (status != EXIT_SUCCESS){
		goto CleanUp;
	}
	current_pos = 0;
	status = vector_at((heap->v), current_pos, &current_element);
	if (status != EXIT_SUCCESS)
	{
		goto CleanUp;
	}

	

	do
	{
		if (LEFT(current_pos) < heap_size)
		{
			status = vector_at((heap->v), LEFT(current_pos), &left_element);
			if (status != EXIT_SUCCESS)
			{
				goto CleanUp;
			}

			if (left_element > current_element)
			{
				largest = LEFT(current_pos);
			}
			else
			{
				largest = current_pos;
			}
		}
		else
		{
			largest = current_pos;
		}

		if (RIGHT(current_pos) < heap_size){

			status = vector_at((heap->v), RIGHT(current_pos), &right_element);
			if (status != EXIT_SUCCESS)
			{
				goto CleanUp;
			}
			if (left_element > current_element)
			{
				largest = RIGHT(current_pos);
			}
		}
		

		if (largest != current_pos){
			heap_swap(heap, current_pos, largest);
			current_pos = largest;
			changed=1;
		}

	} while (changed);

CleanUp:
	return status;
}


int heap_initialized(HEAP* heap){
	return heap != NULL && vector_initialized(heap->v) && heap->comp != NULL;
}


int heap_deallocate(HEAP** heap){

	int status;

	status = EXIT_SUCCESS;

	if (NULL == heap){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	status = vector_deallocate(&(*heap)->v);
	free(*heap);
	*heap = NULL;



CleanUp:
	return status;
}

