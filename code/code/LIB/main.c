#include<stdio.h>
#include"Vector.h"
#include"Tree.h"
#include"Heap.h"
#include"List.h"
#include"HashTable.h"
#include<stdlib.h>
#include<time.h>
int main(){
	
	VECTOR a;
	vector_init(&a);
	vector_insert(&a, 1);

	vector_insert(&a, 1);
	printf("%d\n",  vector_insert(&a, 1));
	printf("%d", a.elems[2]);


	TREE t;
	HEAP h;
	LIST l;
	heap_init(&h, heap_min_heap_comp);
	tree_init(&t);
	tree_insert(&t, 1);

	tree_insert(&t, 3);
	tree_insert(&t, 4);
	tree_insert(&t, 2);
	tree_insert(&t, 6);
	tree_insert(&t, 5);
	int s = 1;
	//for (int i = 1; i < 10000000; i++, i % 10000 == 0 ? (printf("da\n")) : (s++))tree_insert(&t, i);
	//for (int i = 1; i < 10000000; i++ , i % 10000 == 0 ? (printf("nu\n")) : (s++))tree_delete(&t, i);

	list_init(&l);
	srand(time(NULL));
	//for (int i = 0; i < 10000000; i += 3)list_insert(&l, i);

	//for (int i = 2; i < 10000000; i += 3)list_insert(&l, i);

	//for (int i = 1; i < 10000000; i += 3)list_insert(&l, i);

	LIST sorted_list;
	list_init(&sorted_list);
	list_merge_sort(&l, &sorted_list);



	HASH_TABLE ht;
	hash_table_init(&ht);
	for (int i = 0; i < 400; i++)
		hash_table_insert(&ht, i);

	ht.t[5];
	return 0;
}