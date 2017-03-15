#include<stdio.h>
#include"Utils.h"
#include"Comands.h"

#define WRITER_BUFFER_SIZE 1024

typedef struct _WRITER{
	FILE* file;

	char* buffer;
	unsigned int buffer_current_pos;

}WRITER;


STATUS writer_init(WRITER* writer, char* file_name);

STATUS writer_write_line(WRITER* writer, char* line);

