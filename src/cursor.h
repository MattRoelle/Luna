#ifndef CURSOR_H_
#define CURSOR_H_

#include "row.h"
#include "types.h"

typedef struct Cursor {
  Row *row;
  short col;
} Cursor;

luna cursor_set_position(Cursor*, Row*, short);
luna cursor_move_left(Cursor*, Row*);
luna cursor_move_right(Cursor*, Row*);
luna cursor_move_up(Cursor*, Row*, int);
luna cursor_move_down(Cursor*, Row*, int);


#endif
