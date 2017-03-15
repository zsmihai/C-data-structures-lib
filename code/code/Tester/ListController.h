
#include<List.h>
#include"Utils.h"
#include "TestReader.h"
#include"TestWriter.h"

#define MAX_NR_LISTS 10
#define MAX_ELEMENTS_LIST 10000000

typedef struct _LIST_CONTROLLER{
	LIST lists[MAX_NR_LISTS];

	int current_list;
	int nr_lists;

}LIST_CONTROLLER;


STATUS list_controller_init(LIST_CONTROLLER* list_controller);

STATUS list_controller_deallocate(LIST_CONTROLLER* list_controller);


STATUS list_controller_goto(LIST_CONTROLLER* list_controller, READER* reader);

STATUS list_controller_read(LIST_CONTROLLER* list_controller, READER* reader);

STATUS list_controller_add(LIST_CONTROLLER* list_controller, READER* reader, WRITER* writer);

STATUS list_controller_merge(LIST_CONTROLLER* list_controller);

STATUS list_controller_merge_sort(LIST_CONTROLLER* list_controller);

STATUS list_controller_print(LIST_CONTROLLER* list_controller, WRITER* writer);
