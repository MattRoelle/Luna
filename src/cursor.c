#include "cursor.h"
#include "row.h"
#include "types.h"
#include "buffer.h"

luna cursor_set_position(Cursor* cursor, Row* row, short col) {
  if (row == NULL) {
    return NONEXISTENT_ROW;
  } else if (col < 0 || col > row->length) {
    return INVALID_COL;
  } else {
    cursor->row = row;
    cursor->col = col;
    return SUCCESS;
  }
}

luna cursor_move_left(Cursor* cursor, Row* row) {
  if (cursor->col - 1 >= 0) {
    cursor->col--;
    return SUCCESS;
  }
  return BEGINNING_OF_ROW;
}

luna cursor_move_right(Cursor* cursor, Row* row) {
  if (cursor->col + 1 < row->length) {
    cursor->col++;
    return SUCCESS;
  }
  return END_OF_ROW;
}

luna cursor_move_up(Cursor* cursor, Row* row, int id) {
  Buffer *target = get_buffer(id);
  if (target == NULL) {
    return INVALID_ID;
  } else {
    int row_index = get_row_in_buffer(target, row);
    if (row_index - 1 < 0) { 
      /* If the row_index is nonexistent OR trying to move past the top row */
      return NONEXISTENT_ROW;
    } else {
      cursor->row = &target->rows[row_index - 1];
      return SUCCESS;
    }
  }
}

luna cursor_move_down(Cursor* cursor, Row* row, int id) {
  Buffer *target = get_buffer(id);
  if (target == NULL) {
    return INVALID_ID;
  } else {
    int row_index = get_row_in_buffer(target, row);
    if (row_index + 1 >= target->n_rows) { 
      /* If the row_index is nonexistent OR trying to move past the bottom row */
      return NONEXISTENT_ROW;
    } else {
      cursor->row = &target->rows[row_index + 1];
      return SUCCESS;
    }
  }
}
