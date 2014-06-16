#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>

#include "display_utils.h"
#include "types.h"
#include "buffer.h"
#include "row.h"
#include "cursor.h"

luna init_display() {
  initscr();
  raw();
  noecho();
  keypad(stdscr, true);
  return SUCCESS;
}

luna draw_buffer(int id) {
  int SCR_W, SCR_H, rawrow, i;
  getmaxyx(stdscr, SCR_H, SCR_W);

  Buffer *target = get_buffer(id);
  if (target == NULL) {
    return INVALID_ID;
  } else {
    printf("before while loop\n");
    rawrow = 0;
    i = 0;
    while (rawrow < SCR_H && i < target->n_rows) {
      printf("%d\n", i);
      printf("%s\n", target->rows[i].content);
      mvprintw(rawrow, 0, target->rows[i].content);
      if (target->rows[i].length > SCR_W) {
        rawrow++;
      }
      rawrow++;
      i++;
    }
  }
  return SUCCESS;
}

luna end_display() {
  endwin();
  return SUCCESS;
}
