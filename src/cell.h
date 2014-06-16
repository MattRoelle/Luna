#ifndef CELL_H
#define CELL_H

typedef struct cell {
  char content;
  char *flags;
} Cell;

void cell_set_content(Cell*, char);
void cell_set_flags(Cell*, char*);
#endif
