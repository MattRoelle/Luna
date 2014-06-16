#ifndef DISPLAY_UTILS_H
#define DISPLAY_UTILS_H

#include <ncurses.h>

#include "types.h"

luna init_display();
luna draw_buffer(int);

luna end_display();

#endif
