#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "LUA.h"
#include "cursor.h"
#include "row.h"
#include "types.h"

void init_buffers() {
  open_buffers = (Buffer *)calloc(1, sizeof(Buffer));
  n_buffers = 0;
  active_buffer = 1;
}

luna create_buffer_from_scratch() {
  n_buffers++;
  Buffer new_buffer = (Buffer){
    .id = n_buffers,
    .index = n_buffers - 1,
    .f_name = NULL,
    .content_buffer = "",
    .n_rows = 0,
    .rows = (Row *)calloc(1, sizeof(Row)),
  };

  new_buffer.curs = (Cursor){
    .row = &new_buffer.rows[0],
    .col = 0
  };

  Buffer *tmp;
  tmp = (Buffer *)realloc(open_buffers, n_buffers * sizeof(Buffer));
  if (tmp) { open_buffers = tmp; }
  else { return OOM; }

  open_buffers[n_buffers - 1] = new_buffer;

  add_new_row_to_buffer(n_buffers);

  return new_buffer.id;
}

int create_buffer_from_file(char *f_name) {
  // TODO: Actually open a file
  create_buffer_from_scratch();
  return 0;
}

Buffer* get_buffer(int id) {
  int i;
  for(i = 0; i < n_buffers; i++) {
    if (open_buffers[i].id == id) {
      return &open_buffers[i];
    }
  }
  return NULL;
}

luna get_row_in_buffer(int id, Row* row) {
  int i;
  Buffer *target = get_buffer(id);
  if (target == NULL) {
    return INVALID_ID;
  } else {
    for(i = 0; i < target->n_rows; i++) {
      if (&target->rows[i] == row) {
        return i;
      }
    }
  }
  return SUCCESS;
}

luna switch_buffer(int id) {
  if (id > n_buffers || id < 1) {
    return INVALID_ID;
  } else {
    active_buffer = id;

    return id;
  }
}

luna add_new_row_to_buffer(int id) {
  Buffer *target = get_buffer(id);
  if (target == NULL) {
    return INVALID_ID;
  } else {
    size_t old_size;

    int i;
    for(i = 0; i < target->n_rows; i++) {
      old_size += sizeof(Row);
      old_size += target->rows[i].length * sizeof(char);
    }

    Row *tmp;
    tmp = (Row *)malloc(old_size + sizeof(Row));
    if (tmp) { target->rows = tmp; }
    else { return OOM; }

    target->n_rows++;

    target->rows[target->n_rows - 1] = (Row){
      .content = "",
      .length = 0
    };
  }
  return SUCCESS;
}

luna insert_row_in_buffer(int id, int index) {
  Buffer *target = get_buffer(id);
  if (target == NULL) {
    return INVALID_ID;
  } else {
    Row *tmp;

    target->n_rows++;
    tmp = (Row *)realloc(target->rows, sizeof(Row) * target->n_rows);
    if (tmp) { target->rows = tmp; }
    else { return OOM; }

    memcpy(&target->rows[index + 1], &target->rows[index], sizeof(Row) * (target->n_rows - index));
    target->rows[index] = (Row){
      .content = "",
      .length = 0
    };
  }
  return 1;
}

luna remove_row_from_buffer(int id, int index) {
  Buffer *target = get_buffer(id);
  if (target == NULL) {
    return INVALID_ID;
  } else {
    Row *tmp;

    target->n_rows--;

    memcpy(&target->rows[index], &target->rows[index + 1], sizeof(Row) * (target->n_rows - index));

    tmp = (Row *)realloc(target->rows, sizeof(Row) * target->n_rows);
    if (tmp) { target->rows = tmp; }
    else { return OOM; }
  }
  return 1;
}

void save_buffer(int id, char *f_name) {

}

luna destroy_buffer(int id) {
  Buffer *buffer_to_delete = get_buffer(id);
  if (buffer_to_delete == NULL) {
    return INVALID_ID;
  } else {
    Buffer *tmp;

    if (get_buffer(active_buffer)->index >= buffer_to_delete->index) {
      active_buffer--;
    }

    memcpy(&open_buffers[buffer_to_delete->index], &open_buffers[buffer_to_delete->index + 1], sizeof(Buffer) * (n_buffers - buffer_to_delete->index));
    n_buffers--;
    tmp = (Buffer *)realloc(open_buffers, n_buffers * sizeof(Buffer));
    if (tmp) { open_buffers = tmp; }
    else { return OOM; }

    int i;
    for(i = 0; i < n_buffers; i++) {
      open_buffers[i].index = i;
    }

    return SUCCESS;
  }
}
