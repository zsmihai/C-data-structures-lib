#include"Vector.h"
#include"Status.h"
#include<stdlib.h>

int vector_init(VECTOR* v);

int vector_create(VECTOR **v){
	int status;
	VECTOR* new_vector;

	status = EXIT_SUCCESS;
	new_vector = NULL;

	if (NULL == v){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	new_vector = (VECTOR*)malloc(sizeof(VECTOR));

	if (NULL == new_vector){
		status = STATUS_MALLOC_FAIL;
		goto CleanUp;
	}

	vector_init(new_vector);
	*v = new_vector;

CleanUp:
	if (status != EXIT_SUCCESS){
		if (new_vector != NULL)
			vector_deallocate(&new_vector);
	}
	return status;
}
int vector_init(
	VECTOR *v)
{
	int status;

	status = EXIT_SUCCESS;


	if (NULL == v){
		status =  STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	v->elems = malloc(VECTOR_INIT_CAPACITY * sizeof(int));

	if (NULL == v->elems){
		status = STATUS_MALLOC_FAIL;
		goto CleanUp;
	}

	v->size = 0;
	v->capacity = VECTOR_INIT_CAPACITY;

CleanUp:
	return status;
}



int vector_at(VECTOR* v, unsigned int position, int* element){
	int status;


	status = EXIT_SUCCESS;

	if (NULL == v){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	if (!vector_initialized(v)){
		status = STATUS_NOT_INITIALIZED;
		goto CleanUp;
	}


	if (v->size <= position){
		status = STATUS_INDEX_OUT_OF_BOUNDS;
		goto CleanUp;
	}

	*element = v->elems[position];

CleanUp:
	return status;

}




static int vector_resize(
	VECTOR *v
	){

	int *new_elems;
	int status;

	new_elems = NULL;
	status = EXIT_SUCCESS;

	if (NULL == v){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}
	

	v->capacity = VECTOR_RESIZE_RATIO * v->capacity;
	new_elems = (int*)realloc(v->elems, v->capacity * sizeof(int) );
	v->elems = NULL;

	if (NULL == new_elems){
		status = STATUS_MALLOC_FAIL;
		goto CleanUp;
	}

	v->elems = new_elems;
	

	CleanUp:
	new_elems = NULL;
	return status;
}


int vector_insert(
	VECTOR *v, 
	int element)
{
	int status;


	status = EXIT_SUCCESS;

	if (NULL == v){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	if (!vector_initialized(v)){
		status = STATUS_NOT_INITIALIZED;
		goto CleanUp;
	}

	if (v->size >= v->capacity){
		status = vector_resize(v);

		if (status != EXIT_SUCCESS){
			goto CleanUp;
		}
	}

	v->elems[v->size] = element;
	v->size++;


CleanUp:
	return status;
}

int vector_insert_by_position(VECTOR *v, int element, unsigned int position){
	
	int status;
	
	status = EXIT_SUCCESS;

	if (NULL == v){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	if (!vector_initialized(v)){
		status = STATUS_NOT_INITIALIZED;
		goto CleanUp;
	}


	if (v->size <= position){
		status = STATUS_INDEX_OUT_OF_BOUNDS;
		goto CleanUp;
	}


	v->elems[position] = element;


CleanUp:
	return status;
}



int vector_size(VECTOR *v, int* size){

	int status;

	status = EXIT_SUCCESS;

	if (NULL == v){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	if (!vector_initialized(v)){
		status = STATUS_NOT_INITIALIZED;
		goto CleanUp;
	}
	
	*size = v->size;

CleanUp:
	return status;

	
}



int vector_remove_by_position(VECTOR *v, unsigned int position){

	int status;
	unsigned int i;

	status = EXIT_SUCCESS;

	if (NULL == v){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	if (!vector_initialized(v)){
		status = STATUS_NOT_INITIALIZED;
		goto CleanUp;
	}

	if (v->size <= position){
		status = STATUS_INDEX_OUT_OF_BOUNDS;
		goto CleanUp;
	}

	for (i = position; i < (v->size - 1) ; i++){
		v->elems[i] = v->elems[i + 1];
	}

	v->size--;
CleanUp:
	return status;
}

int vector_remove_by_value_all(VECTOR *v, int element){

	int status;
	int nr_elements_deleted;
	unsigned int i;

	status = EXIT_SUCCESS;
	nr_elements_deleted = 0;
	i = 0;


	if (NULL == v){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	if (!vector_initialized(v)){
		status = STATUS_NOT_INITIALIZED;
		goto CleanUp;
	}
	for (i = 0; i < v->size; i++){

		if (v->elems[i] == element)
		{
			nr_elements_deleted++;
		}
		else
		{
			v->elems[i - nr_elements_deleted] = v->elems[i];
		}
	}
	
	v->size -= nr_elements_deleted;


CleanUp:
	return status;
}


int vector_deallocate(VECTOR **v){

	int status;

	status = EXIT_SUCCESS;

	if (NULL == v){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}


	free((*v)->elems);
	(*v)->elems = NULL;
	free(*v);
	*v = NULL;


CleanUp:
	return status;
}

int vector_initialized(VECTOR* v){
	return v != NULL && v->elems != NULL;
}