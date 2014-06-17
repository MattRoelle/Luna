#ifndef DISPLAY_UTILS_H
#define DISPLAY_UTILS_H

#include <ncurses.h>

#include "types.h"

luna init_display();

luna draw_buffer(int);
luna draw_cursor(int, int);
luna draw_status_line();

luna echo_to_status_line(char *);

luna end_display();

#endif
