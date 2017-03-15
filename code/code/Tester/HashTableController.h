
#include<HashTable.h>
#include"Utils.h"
#include "TestReader.h"
#include"TestWriter.h"

#define MAX_NR_HASH_TABLES 10
#define MAX_ELEMENTS_HASH_TABLE 10000000

typedef struct _HASH_TABLE_CONTROLLER{
	HASH_TABLE hash_tables[MAX_NR_HASH_TABLES];

	int current_hash_table;
	int nr_hash_tables;

}HASH_TABLE_CONTROLLER;


STATUS hash_table_controller_init(HASH_TABLE_CONTROLLER* hash_table_controller);

STATUS hash_table_controller_deallocate(HASH_TABLE_CONTROLLER* hash_table_controller);

STATUS hash_table_controller_goto(HASH_TABLE_CONTROLLER* hash_table_controller, READER* reader);

STATUS hash_table_controller_read(HASH_TABLE_CONTROLLER* hash_table_controller, READER* reader);

STATUS hash_table_controller_search(HASH_TABLE_CONTROLLER* hash_table_controller, WRITER* writer);
