

#define HASH_TABLE_INITIAL_LISTS_NR 37
#define HASH_TABLE_MAX_RATIO 6
#define HASH_TABLE_RESIZE_RATIO 4

#include"List.h"
#include"Utils.h"
typedef struct _Hash_Table{

	unsigned int size;
	LIST** t;
	unsigned int nr_buckets;

}HASH_TABLE;




int hash_table_create(HASH_TABLE **hash_table);

int hash_table_insert(HASH_TABLE* hash_table, int element);

BOOL hash_table_find(HASH_TABLE*hash_table, int element);

static int hash_table_hash_function(HASH_TABLE* hash_table, int element);

int hash_table_deallocate(HASH_TABLE **hash_table);