#ifndef LINE_H
#define LINE_H

typedef struct row {
  char *content;
  int length;
} Row;

void init_row(Row*);

void append_character_to_row(Row*, char);
void append_sequence_to_row(Row*, int, char*);

void insert_character_in_row(Row*, int, char);
void insert_sequence_in_row(Row*, int, int, char*);

void remove_character_from_row(Row*, int);
void remove_sequence_from_row(Row*, int, int);
#endif
