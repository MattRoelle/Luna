#include <stdbool.h>
#include <ncurses.h>
#include <stdio.h>
#include <math.h>

#include "display_utils.h"
#include "types.h"
#include "buffer.h"
#include "row.h"
#include "cursor.h"
#include "input.h" //TODO REMOVE

luna init_display() {
  initscr();
  raw();
  noecho();
  keypad(stdscr, true);
  curs_set(0);
  if (has_colors()) {
    start_color();
  }
  return SUCCESS;
}

luna draw_buffer(int id) {
  int SCR_W, SCR_H, line_number_offset;

  getmaxyx(stdscr, SCR_H, SCR_W);

  Buffer *target = get_buffer(id);
  if (target == NULL) {
    return INVALID_ID;
  } else {
    line_number_offset = floor(log10(abs(target->n_rows + 1))) + 2;
    char line_number[line_number_offset + 1];
    int i = 0;
    int rawrow;
    for(rawrow = 0; rawrow < SCR_H; rawrow++) {
      if (i >= target->n_rows) {
        mvaddch(rawrow, 0, '~');
      } else {
        sprintf(line_number, "%d", i + 1);
        mvaddch(rawrow, line_number_offset - 1, '|');
        mvprintw(rawrow, 0, line_number);
        if (target->rows[i].length > 0) {
          mvprintw(rawrow, line_number_offset, target->rows[i].content);
        }
        if (target->rows[i].length > SCR_W) {
          rawrow++;
        }
      }
      i++;
    }
    draw_cursor(id, line_number_offset);
    draw_status_line();
  }
  return SUCCESS;
}

luna draw_cursor(int id, int offset) {
  int row, col;
  Buffer *target = get_buffer(id);
  if (target == NULL) {
    return INVALID_ID;
  } else {
    col = target->curs.col + offset;
    row = get_row_in_buffer(id, target->curs.row) - 1;

    char c = mvinch(row, col) & A_CHARTEXT;

    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(1));
    mvaddch(row, col, c);
    attroff(COLOR_PAIR(1));
  }
}

luna draw_status_line() {
  int SCR_H, SCR_W;

  getmaxyx(stdscr, SCR_H, SCR_W);

  Buffer *target = get_buffer(active_buffer);
  if (target == NULL) {
    return INVALID_ID;
  } else {
    int col;
    for(col = 0; col < SCR_W; col++) {
      init_pair(1, COLOR_BLACK, COLOR_WHITE);
      attron(COLOR_PAIR(1));
      mvaddch(SCR_H - 1, col, ' ');

      // display input buffer
      mvprintw(SCR_H -1, 2, input_buffer);

      attroff(COLOR_PAIR(1));
    }
  }
  return SUCCESS;
}

luna echo_to_status_line(char *s) {
  int SCR_H, SCR_W;

  getmaxyx(stdscr, SCR_H, SCR_W);
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  attron(COLOR_PAIR(1));

  mvprintw(SCR_H - 1, 38, s);

  attroff(COLOR_PAIR(1));
}

luna end_display() {
  endwin();
  return SUCCESS;
}
