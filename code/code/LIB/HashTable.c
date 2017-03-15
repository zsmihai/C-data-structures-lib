#include"HashTable.h"
#include<stdlib.h>
#include"Status.h"

static int hash_table_init(HASH_TABLE* hash_table, unsigned int nr_buckets);

int hash_table_create(HASH_TABLE **hash_table)
{
	int status;
	HASH_TABLE* new_hash_table;
	
	status = EXIT_SUCCESS;
	new_hash_table = NULL;


	if (NULL == hash_table){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	new_hash_table = (HASH_TABLE*)malloc(sizeof(HASH_TABLE));

	if (new_hash_table == NULL){
		status = STATUS_MALLOC_FAIL;
		goto CleanUp;
	}
	
	status = hash_table_init(new_hash_table, HASH_TABLE_INITIAL_LISTS_NR);
	if (status != EXIT_SUCCESS)
		goto CleanUp;

	*hash_table = new_hash_table;

CleanUp:

	if (status != EXIT_SUCCESS){

		if (new_hash_table != NULL)
			hash_table_deallocate(&new_hash_table);

	}
	return status;
}


int hash_table_init(HASH_TABLE* hash_table, unsigned int nr_buckets){
	int status;
	unsigned int i;
	status = EXIT_SUCCESS;
	
	if (NULL == hash_table){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	hash_table->size = 0;
	hash_table->nr_buckets = HASH_TABLE_INITIAL_LISTS_NR;

	hash_table->t =  (LIST**) malloc(nr_buckets * sizeof(LIST*));
	if (NULL == hash_table){
		status = STATUS_MALLOC_FAIL;
		goto CleanUp;
	}

	for (i = 0; i <= hash_table->nr_buckets; i++){
		status = list_create(&hash_table->t[i]);
		if (status != EXIT_SUCCESS){
			goto CleanUp;
		}
	}

CleanUp:
	return status;


}


int hash_table_insert(HASH_TABLE *hash_table, int element){
	int status;

	status = EXIT_SUCCESS;

	if (NULL == hash_table){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	list_insert(hash_table->t[hash_table_hash_function(hash_table, element)], element);
	
CleanUp:
	return status;

}

static int hash_table_hash_function(HASH_TABLE* hash_table, int element){

	return element % hash_table->nr_buckets;

}

int hash_table_resize(HASH_TABLE* hash_table){

	int status;
	int i;
	int old_bucket_nr;
	LIST** old_lists, **new_lists;
	LIST_NODE* current_node;



	status = EXIT_SUCCESS;

	if (NULL == hash_table){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	old_lists = hash_table->t;
	old_bucket_nr = hash_table->nr_buckets;
	new_lists = (LIST**)malloc(HASH_TABLE_RESIZE_RATIO* hash_table->nr_buckets * sizeof(LIST*));
	if (NULL == new_lists){
		status = STATUS_MALLOC_FAIL;
		goto CleanUp;
	}

	hash_table->t = new_lists;
	hash_table->nr_buckets = HASH_TABLE_RESIZE_RATIO * old_bucket_nr;

	for (i = 0; i <= old_bucket_nr; i++){
		current_node = hash_table->t[i]->first;
		while (current_node != NULL){
			status = hash_table_insert(hash_table, current_node->data);
			if (status != EXIT_SUCCESS){
				goto CleanUp;
			}
			current_node = current_node->next;
		}
	}

	for (i = 0; i <= old_bucket_nr; i++){
		list_deallocate(&old_lists[i]);
	}

	free(old_lists);



CleanUp:
	return status;
}


int hash_table_deallocate(HASH_TABLE **hash_table){

	int status;
	unsigned int i;
	status = EXIT_SUCCESS;

	if (NULL == hash_table){
		status = STATUS_INVALID_PARAMETER_1;
		goto CleanUp;
	}

	for (i = 0; i < (*hash_table)->nr_buckets; i++){
		status = list_deallocate(&(*hash_table)->t[i]);

		if (status != EXIT_SUCCESS)
			goto CleanUp;
	}

	free((*hash_table)->t);
	(*hash_table)->t = NULL;
	free(*hash_table);
	*hash_table = NULL;

CleanUp:
	return status;

}