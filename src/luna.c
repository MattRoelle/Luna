#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#include "state.h"
#include "row.h"
#include "display_utils.h"
#include "cursor.h"
#include "buffer.h"

int main(int argc, char **argv) {
  init_state();
  init_buffers();

  /*

  if (argc == 1) {
    // no file or options were passed
    create_buffer_from_scratch();
  } else {
    // file(s) or options were passed to edit
    int i;
    for(i = 1; i < argc; i++) {
      char* arg = argv[i];
      if (arg[0] == '-') {
        switch(arg[1]) {
          default:
            break;
        }
      } else {
        create_buffer_from_file(arg);
      }
    }
    if (n_buffers == 0) {
      create_buffer_from_scratch();
    }
  }

  */

  create_buffer_from_scratch();

  init_display();

  Buffer *target = get_buffer(0);

  Row *rrows;
  rrows = calloc(3, sizeof(Row));
  rrows[0] = (Row){ .content = "Asdq", .length = 4 };
  rrows[1] = (Row){ .content = "Asdqe", .length = 5 };
  rrows[2] = (Row){ .content = "Asdqeee", .length = 7 };
  
  target->rows = rrows;

  draw_buffer(0);
  
  getch();

  end_display();

  return 0;
}
