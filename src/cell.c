#include "cell.h"

void cell_set_content(Cell* cell, char content) {
  cell->content = content;
}

void cell_set_flags(Cell* cell, char *flags) {
  cell->flags = flags;
}
