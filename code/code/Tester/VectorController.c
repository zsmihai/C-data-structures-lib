#include"VectorController.h"
#include<stdlib.h>

STATUS vector_controller_init(VECTOR_CONTROLLER* vector_controller){
	STATUS status;
	int i;

	status = EXIT_SUCCESS;

	if (NULL == vector_controller)
	{
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	vector_controller->current_vector = NO_CURRENT_VECTOR;
	vector_controller->nr_vectors = 0;

	for (int i = 0; i < MAX_NR_VECTORS; i++)
		vector_controller->vectors[i] = NULL;


CleanUp:
	return status;
}

STATUS vector_controller_deallocate(VECTOR_CONTROLLER* vector_controller){
	STATUS status;
	int i;

	status = EXIT_SUCCESS;

	if (NULL == vector_controller)
	{
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}


	for (int i = 0; i < MAX_NR_VECTORS; i++){
		if (NULL != vector_controller->vectors[i]){
			vector_deallocate(&vector_controller->vectors[i]);
		}
	}
CleanUp:
	return status;
}


STATUS vector_controller_goto(VECTOR_CONTROLLER* vector_controller, READER* reader)
{
	STATUS status;
	int new_current;

	status = EXIT_SUCCESS;
	new_current = NO_CURRENT_VECTOR;

	if (NULL == vector_controller)
	{
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}
	if (NULL == reader)
	{
		status = STATUS_INVALID_PARAMETER_2;
		goto CleanUp;
	}

	status = reader_get_next_int(reader, &new_current);

	if (status != EXIT_SUCCESS){
		goto CleanUp;
	}

	
	status = reader_read_empty_line(reader);

	if (status != EXIT_SUCCESS){
		goto CleanUp;
	}

	if (new_current < 0 || new_current >= MAX_NR_VECTORS){
		status = INDEX_OUT_OF_BOUNDS;
		goto CleanUp;
	}

	vector_controller->current_vector = new_current;


CleanUp:
	return status;
}

STATUS vector_controller_read(VECTOR_CONTROLLER* vector_controller, READER* reader){
	STATUS status;
	int new_current;
	int element;
	int v_size;

	status = EXIT_SUCCESS;
	new_current = NO_CURRENT_VECTOR;
	v_size = 0;

	if (NULL == vector_controller)
	{
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}
	if (NULL == reader)
	{
		status = STATUS_INVALID_PARAMETER_2;
		goto CleanUp;
	}


	if (vector_controller->nr_vectors >= MAX_NR_VECTORS){
		status = NUMBER_OF_STRUCTURES_EXCEEDED;
		goto CleanUp;
	}

	vector_controller->current_vector = vector_controller->nr_vectors;

	status = vector_create(&vector_controller->vectors[vector_controller->current_vector]);
	if (status != EXIT_SUCCESS){
		goto CleanUp;
	}


	while (reader_get_next_int(reader, &element) == EXIT_SUCCESS){

		if (v_size == MAX_ELEMENTS_VECTOR)
		{
			status = CAPACITY_LIMIT_REACHED;
			goto CleanUp;
		}

		status = vector_insert(vector_controller->current_vector, element);
				

		if (status != EXIT_SUCCESS){
			goto CleanUp;
		}

		status = vector_size(vector_controller->current_vector, &v_size);
	}

CleanUp:


	return status;
}

STATUS vector_controller_add(VECTOR_CONTROLLER* vector_controller, READER* reader, WRITER* writer);

STATUS vector_controller_length(VECTOR_CONTROLLER* vector_controller, WRITER* writer);

STATUS vector_controller_remove_position(VECTOR_CONTROLLER* vector_controller, READER* reader, WRITER* writer);

STATUS vector_controller_remove_value(VECTOR_CONTROLLER* vector_controller, READER* reader, WRITER* writer);

STATUS vector_controller_search(VECTOR_CONTROLLER* vector_controller, READER* reader, WRITER* writer);

STATUS vector_controller_print(VECTOR_CONTROLLER* vector_controller, WRITER* writer);
