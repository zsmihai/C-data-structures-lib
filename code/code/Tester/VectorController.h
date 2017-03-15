
#include<Vector.h>
#include"Utils.h"
#include "TestReader.h"
#include"TestWriter.h"
#include<Status.h>
#include"ControllerStatus.h"

#define MAX_NR_VECTORS 10
#define MAX_ELEMENTS_VECTOR 10000000
#define NO_CURRENT_VECTOR -1

typedef struct _VECTOR_CONTROLLER{
	
	VECTOR *vectors[MAX_NR_VECTORS];
	int current_vector;
	int nr_vectors;

}VECTOR_CONTROLLER;


STATUS vector_controller_init(VECTOR_CONTROLLER* vector_controller);

STATUS vector_controller_deallocate(VECTOR_CONTROLLER* vector_controller);


STATUS vector_controller_goto(VECTOR_CONTROLLER* vector_controller, READER* reader);

STATUS vector_controller_read(VECTOR_CONTROLLER* vector_controller, READER* reader);

STATUS vector_controller_add(VECTOR_CONTROLLER* vector_controller, READER* reader, WRITER* writer);

STATUS vector_controller_length(VECTOR_CONTROLLER* vector_controller, WRITER* writer);

STATUS vector_controller_remove_position(VECTOR_CONTROLLER* vector_controller, READER* reader, WRITER* writer);

STATUS vector_controller_remove_value(VECTOR_CONTROLLER* vector_controller, READER* reader, WRITER* writer);

STATUS vector_controller_search(VECTOR_CONTROLLER* vector_controller, READER* reader, WRITER* writer);

STATUS vector_controller_print(VECTOR_CONTROLLER* vector_controller, WRITER* writer);
