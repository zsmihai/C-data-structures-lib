#include"Vector.h"

#define LEFT(x) (2*x+1)
#define RIGHT(x) (2*x+2)
#define PARENT(x) ((x-1)/2)


typedef struct _HEAP{

	VECTOR* v;
	
	int(*comp)(int, int);

}HEAP;



int heap_create(HEAP** heap, int(*comp)(int, int));

int heap_min_heap_comp(int el1, int el2);

int heap_max_heap_comp(int el1, int el2);

int heap_push(HEAP* heap, int element);

int heap_pop(HEAP* heap);

int heap_top(HEAP* heap, int *element);

int heap_initialized(HEAP* heap);

int heap_deallocate(HEAP** heap);