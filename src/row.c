#include "row.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_row(Row* row) {
  row->length = 0;
  row->content = (char *)calloc(1, sizeof(char));
}

void append_character_to_row(Row* row, char c) {
  row->length++;
  void *tmp = (char *)realloc(row->content, sizeof(char) * row->length);
  if (tmp) { row->content = tmp; }

  row->content[row->length - 1] = c;
}

void insert_character_in_row(Row* row, int index, char c) {
  row->length++;
  void *tmp = (char *)realloc(row->content, sizeof(char) * row->length);
  if (tmp) { row->content = tmp; }

  memcpy(&row->content[index + 1], &row->content[index], sizeof(char) * (row->length - index));
  row->content[index] = c;
}

void remove_character_from_row(Row* row, int index) {
  memcpy(&row->content[index], &row->content[index + 1], sizeof(char) * (row->length - index));
  row->length--;
  char *tmp = calloc(row->length, sizeof(char));
  memcpy(tmp, row->content, sizeof(char) * row->length);
  free(row->content);
  row->content = tmp;
}

void remove_sequence_from_row(Row* row, int index, int len) {
  row->length -= len;
  memcpy(&row->content[index], &row->content[index + len], sizeof(char) * (row->length - (index + len)));
  void *tmp = (char *)realloc(row->content, sizeof(char) * row->length);
  if (tmp) { row->content = tmp; }
}
