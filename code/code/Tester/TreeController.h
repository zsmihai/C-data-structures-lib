
#include<Tree.h>
#include"Utils.h"
#include "TestReader.h"
#include"TestWriter.h"

#define MAX_NR_TREES 10
#define MAX_ELEMENTS_TREE 10000000

typedef struct _TREE_CONTROLLER{
	TREE trees[MAX_NR_TREES];

	int current_tree;
	int nr_trees;

}TREE_CONTROLLER;


STATUS tree_controller_init(TREE_CONTROLLER* tree_controller);

STATUS tree_controller_deallocate(TREE_CONTROLLER* tree_controller);

STATUS tree_controller_goto(TREE_CONTROLLER* tree_controller, READER* reader);

STATUS tree_controller_read(TREE_CONTROLLER* tree_controller, READER* reader);

STATUS tree_controller_insert(TREE_CONTROLLER* tree_controller, READER* reader);

STATUS tree_controller_search(TREE_CONTROLLER* tree_controller, WRITER* writer);

STATUS tree_controller_remove(TREE_CONTROLLER* tree_controller, READER* reader);
