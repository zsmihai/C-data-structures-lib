#include<stdio.h>
#include"Utils.h"
#include"Comands.h"

#define READER_BUFFER_SIZE 1024

typedef struct _READER{
	FILE* file;
	char* buffer;
	unsigned int buffer_current_pos;

}READER;


STATUS reader_init(READER* reader, char* file_name);

STATUS reader_close(READER* reader);

STATUS reader_deallocate(READER* reader);

STATUS reader_get_next_string(READER* reader, char* string);

STATUS reader_get_next_int(READER* reader, int* data);

STATUS reader_read_empty_line(READER* reader);

STATUS reader_read_line(READER* reader);
