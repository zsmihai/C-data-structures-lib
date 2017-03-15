#include<stdlib.h>



 struct NODE{
	int data;
	int height;
	struct NODE *left, *right;
};
 
 typedef struct NODE NODE;

typedef struct _TREE{
	NODE *root;
}TREE;



int tree_create(TREE** tree);

int tree_insert(TREE* tree, int element);

void tree_delete(TREE* tree, int element);

int tree_find(TREE* tree, int element);

int tree_deallocate(TREE** tree);

