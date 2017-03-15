
#ifndef _VECTOR_H_
#define _VECTOR_H_

#define VECTOR_RESIZE_RATIO 2
#define VECTOR_INIT_CAPACITY 5

typedef struct _VECTOR {
	unsigned int capacity;
	unsigned int size;
	int* elems;

}VECTOR;



int vector_create(VECTOR **v);

static int vector_resize(VECTOR *v);

int vector_insert(VECTOR *v, int element);

int vector_insert_by_position(VECTOR *v, int element, unsigned int position);

int vector_remove_by_position(VECTOR *v, unsigned int position);

int vector_remove_by_value(VECTOR *v, int element);	

int vector_remove_by_value_all(VECTOR *v, int element);

int vector_at(VECTOR* v, unsigned int position, int* element);

int vector_initialized(VECTOR *v);

int vector_deallocate(VECTOR **v);

int vector_size(VECTOR *v, int* size);

#endif