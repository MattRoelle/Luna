#ifndef BUFFER_H
#define BUFFER_H

#include "cursor.h"
#include "row.h"
#include "types.h"

#include <stdio.h>

typedef struct Buffer {
    int id;
    int index;
    char *f_name;
    char *content_buffer;
    Row *rows;
    int n_rows;
    Cursor curs;
} Buffer;

Buffer *open_buffers;
int n_buffers;
int active_buffer;

void init_buffers();

luna create_buffer_from_scratch();
int create_buffer_from_file(char *);

luna get_row_in_buffer(int, Row*);

Buffer* get_buffer(int);

luna switch_buffer(int);

luna add_new_row_to_buffer(int);
luna insert_row_in_buffer(int, int);
luna remove_row_from_buffer(int, int);

void save_buffer(int, char *);
luna destroy_buffer(int);
#endif
