#ifndef TYPES_H
#define TYPES_H

typedef enum {
  NORMAL,
  EDIT,
  COMMAND,
  EXIT
} state;

typedef enum {
  OOM,
  SUCCESS,
  INVALID_ID,
  END_OF_ROW,
  BEGINNING_OF_ROW,
  INVALID_COL,
  NONEXISTENT_ROW
} luna;

#endif
