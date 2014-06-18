#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "types.h"
#include "input.h"
#include "state.h"
#include "row.h"
#include "display_utils.h"
#include "cursor.h"
#include "buffer.h"
#include "LUA.h"

int main(int argc, char **argv) {
  init_state();
  init_buffers();
  init_LUA();

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
          case 'h':
            printf("Luna, A text editor, and then some.\n");
            printf("WTFPL Licensed\n");
            return 0;
            break;
          case 'v':
            printf("Luna v0.01\n");
            return 0;
            break;
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

  init_display();

  while (luna_state != EXIT) {
    draw_buffer(active_buffer);
    get_input();
  
    lua_getglobal(L, "check_keybindings");
    if (lua_pcall(L, 0, 0, 0) != 0) {
      error(L, "Keybinding Error: %s", lua_tostring(L, -1));
    }

  }

  end_display();
  end_LUA();

  return 0;
}
