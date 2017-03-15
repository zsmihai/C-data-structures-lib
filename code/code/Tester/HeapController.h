
#include<Heap.h>
#include"Utils.h"
#include"TestReader.h"
#include"TestWriter.h"

#define MAX_NR_HEAPS 10
#define MAX_ELEMENTS_HEAP 10000000

typedef struct _HEAP_CONTROLLER{
	HEAP heaps[MAX_NR_HEAPS];

	int current_heap;
	int nr_heaps;

}HEAP_CONTROLLER;


STATUS heap_controller_init(HEAP_CONTROLLER* heap_controller);

STATUS heap_controller_deallocate(HEAP_CONTROLLER* heap_controller);

STATUS heap_controller_goto(HEAP_CONTROLLER* heap_controller, READER* reader);

STATUS heap_controller_read(HEAP_CONTROLLER* heap_controller, READER* reader);

STATUS heap_controller_add(HEAP_CONTROLLER* heap_controller, READER* reader);

STATUS heap_controller_remove(HEAP_CONTROLLER* heap_controller, WRITER* writer);
