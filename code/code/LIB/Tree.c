#include"Tree.h"
#include"Status.h"

static NODE* srs(NODE* node);

static NODE* srd(NODE* node);

static NODE* drs(NODE* node);

static NODE* drd(NODE* node);

static void node_set_height(NODE* node);

static NODE* tree_insert_rec(NODE* node, NODE* element);

static int node_height(NODE* node);

static NODE* tree_min(NODE* node);

static void node_deallocate(NODE** node);

static NODE* delete_rec(NODE* root, int element);

static NODE* tree_balance(NODE* root);


int node_init(NODE *node);
int tree_init(TREE *tree);


int node_create(NODE ** node)
{

	int status;
	NODE* new_node;

	status = EXIT_SUCCESS;
	new_node = NULL;

	if (NULL == node){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	new_node = (NODE*)malloc(sizeof(NODE));

	if (NULL == new_node){
		status = STATUS_MALLOC_FAIL;
		goto CleanUp;
	}

	node_init(new_node);
	*node = new_node;

CleanUp:
	if (status != EXIT_SUCCESS){
		if (new_node != NULL)
			node_deallocate(&new_node);
	}
	return status;
}

int tree_create(TREE** tree){
	int status;
	TREE* new_tree;

	status = EXIT_SUCCESS;
	new_tree = NULL;

	if (NULL == tree){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	new_tree = (TREE*)malloc(sizeof(TREE));

	if (NULL == new_tree){
		status = STATUS_MALLOC_FAIL;
		goto CleanUp;
	}

	tree_init(new_tree);
	*tree = new_tree;

CleanUp:
	if (status != EXIT_SUCCESS){
		if (new_tree != NULL)
			tree_deallocate(&new_tree);
	}
	return status;

}


int node_init(NODE *node){

	int status;

	status = EXIT_SUCCESS;

	if (NULL == node){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}


	node->height = 0;
	node->left = NULL;
	node->right = NULL;


CleanUp:
	return status;
}


int tree_init(TREE *tree){
	int status;

	status = EXIT_SUCCESS;

	if (NULL == tree){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	tree->root = NULL;

CleanUp:
	return status;
}

static int node_height(NODE* node){

	int height;

	if (NULL == node)
		height = -1;
	else
		height = node->height;

	return height;
}


static void node_set_height(NODE *node){

	if (NULL == node)return;
	node->height = 1 + max( node_height(node->left), node_height(node->right) );

}

static NODE* srs(NODE* node){

	NODE* new_root;

	new_root = NULL;

	if (NULL == node)
		return new_root;

	new_root = node->right;

	node->right = new_root->left;
	new_root->left = node;

	node_set_height(node);
	node_set_height(new_root);

	return new_root;
}

static NODE* srd(NODE* node){

	NODE* new_root;

	new_root = NULL;

	if (NULL == node)
		return new_root;

	new_root = node->left;

	node->left = new_root->right;
	new_root->right = node;

	node_set_height(node);
	node_set_height(new_root);

	return new_root;
}

//TODO null pointers... 
static NODE* drs(NODE* node){

	NODE* new_root;

	new_root = NULL;

	if (NULL == node)
		return new_root;

	node->right = srd(node->right);

	new_root = srs(node);

	return new_root;
}

//TODO null pointers... 
static NODE* drd(NODE* node){

	NODE* new_root;

	new_root = NULL;

	if (NULL == node)
		return new_root;

	node->left = srs(node->left);

	new_root = srd(node);

	return new_root;
}


static NODE* tree_balance(NODE* root){


	NODE* new_root;

	new_root = root;

	if (NULL == root){
		new_root = NULL;
		goto CleanUp;
	}

	if (node_height((root->right)) - node_height((root->left)) >= 2){

		if (node_height(root->right->right) >= node_height(root->right->left))
			new_root = srs(root);
		else
			new_root = drs(root);
	}
	else if (node_height((root->left)) - node_height((root->right)) >= 2){

		if ( node_height(root->left->left) >= node_height(root->left->right))
			new_root = srd(root);
		else
			new_root = drd(root);
	}
	
	node_set_height(new_root);

CleanUp:
	return new_root;
}




static NODE* tree_insert_rec(NODE* node, NODE* element){

	NODE* new_root;

	new_root = node;

	if (NULL == node){
		new_root = element;
		goto CleanUp;
	}
	if (element->data > node->data){
		node->right = tree_insert_rec(node->right, element);
		new_root = tree_balance(node);
	}
	else if (element->data < node->data)
	{
		node->left = tree_insert_rec(node->left, element);
		new_root = tree_balance(node);
	}
	
CleanUp:
	return new_root;
}



int tree_insert(TREE* tree, int element)
{

	int status;
	NODE* node;

	node = NULL;
	status = EXIT_SUCCESS;

	if (NULL == tree){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	node = (NODE*)malloc(sizeof(NODE));

	if (NULL == node){
		status = STATUS_MALLOC_FAIL;
		goto CleanUp;
	}
	node_init(node);
	node->data = element;

	tree->root = tree_insert_rec(tree->root, node);

CleanUp:
	return status;
}





static NODE* tree_min(NODE* node){

	NODE* current_node;

	current_node = node;

	while (current_node != NULL && current_node->left != NULL)
		current_node = current_node->left;

	return current_node;

}


static NODE* delete_rec(NODE* root, int element){

	NODE* new_root;
	NODE* min_node;
	new_root = NULL;
	min_node = NULL;

	if (NULL == root){
		new_root = NULL;
		goto CleanUp;
	}

	if (root->data > element){

		root->left = delete_rec(root->left, element);
	
		new_root = root;
		
		
		
		goto Balance;
	}
	if (root->data < element){

		root->right = delete_rec(root->right, element);
		new_root = root;
		goto Balance;



		
	}
	if (root->data == element){


		if (NULL == root->left && NULL == root->right)
		{
			node_deallocate(&root);
			new_root = NULL;
			goto Balance;
		}
		else if (NULL == root->left){
			new_root = root->right;
			node_deallocate(&root);
			goto Balance;
		}
		else if (NULL == root->right){
			new_root = root->left;
			node_deallocate(&root);
			goto Balance; 

		}
		else
		{
			min_node = tree_min(root->right);
			root->data = min_node->data;
			root->right = delete_rec(root->right, element);
			new_root = root;
			goto Balance;
		}
		
	}

Balance:
	new_root = tree_balance(new_root);

CleanUp:
	return new_root;

}

static void node_deallocate(NODE** node){
	free(*node);
	*node = NULL;
}

void tree_delete(TREE* tree, int element){
	
	tree->root = delete_rec(tree->root, element);
}

static void tree_deallocate_rec(NODE* node){

	if (NULL == node)
		return;

	tree_deallocate_rec(node->left);
	tree_deallocate_rec(node->right);

	node_deallocate(&node);
	
}


int tree_deallocate(TREE** tree){

	int status;
	status = EXIT_SUCCESS;

	if (NULL == tree){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	tree_deallocate_rec((*tree)->root);

	free(*tree);
	*tree = NULL;

CleanUp:
	return status;

}