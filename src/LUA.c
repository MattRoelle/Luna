#define SCRIPTS_DIR "./luna."

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <string.h>
#include <ncurses.h>

#include "LUA.h"
#include "types.h"
#include "buffer.h"
#include "row.h"
#include "cursor.h"
#include "state.h"
#include "display_utils.h"

luna init_LUA() {
  L = luaL_newstate();
  luaL_openlibs(L);

  register_luna_functions();
  
  luaL_loadfile(L, "/home/matt/code/Luna/luna./std/std.lua"); // load the std lua scripts
  lua_pcall(L, 0, 0, 0);
  luaL_loadfile(L, "/home/matt/code/Luna/luna./lunarc.lua"); // load the lunarc script
  lua_pcall(L, 0, 0, 0);

  return SUCCESS;
}

luna end_LUA() {
  lua_close(L);

  return SUCCESS;
}

luna register_luna_functions() {
  // redefine LUA's print
  lua_pushcfunction(L, l_print);
  lua_setglobal(L, "print");

  // switch_state(state)
  lua_pushcfunction(L, l_switch_state);
  lua_setglobal(L, "switch_state");

  // get_state()
  lua_pushcfunction(L, l_get_state);
  lua_setglobal(L, "get_state");

  // switch_buffer(id)
  lua_pushcfunction(L, l_switch_buffer);
  lua_setglobal(L, "switch_buffer");

  // move_cursor(drow, dcol)
  lua_pushcfunction(L, l_move_cursor);
  lua_setglobal(L, "move_cursor");

  return SUCCESS;
}

// Functions that are exposed to LUA

int l_print(lua_State *L) {
  char *s = lua_tostring(L, -1);
  echo_to_status_line(s);
  return 0;
}

int l_switch_state(lua_State *L) {
  state new_state;
  char *str_state = lua_tostring(L, -1);

  if (strcmp(str_state, "n") == 0) {
    new_state = NORMAL;
  } else if (strcmp(str_state, "e") == 0) {
    new_state = EDIT;
  } else if (strcmp(str_state, "c") == 0) {
    new_state = COMMAND;
  } else if (strcmp(str_state, "E") == 0) {
    new_state = EXIT;
  }

  change_state(new_state);

  lua_pushstring(L, str_state);
  return 1;
}

int l_get_state(lua_State *L) {
  if (luna_state == NORMAL) {
    lua_pushstring(L, "n");
  } else if (luna_state == EDIT) {
    lua_pushstring(L, "e");
  } else if (luna_state == COMMAND) {
    lua_pushstring(L, "c");
  } else if (luna_state == EXIT) {
    lua_pushstring(L, "E");
  }
  return 1;
}

int l_switch_buffer(lua_State *L) {
  int id = lua_tonumber(L, 1);
  int result = switch_buffer(id);
  lua_pushnumber(L, result);
  return 1;
}

int l_move_cursor(lua_State *L) {
  int drow, dcol;
  Buffer *target;

  target = get_buffer(active_buffer);

  if (target == NULL) {
    lua_pushnumber(L, -1);
  } else {
    Cursor *curs = &target->curs;
    Row *row = curs->row;
    int i = 0;

    drow = lua_tonumber(L, 1);
    dcol = lua_tonumber(L, 2);

    if (drow > 0) {
      for(i = 0; i <= drow; i++) { cursor_move_up(curs, row, target->id); }
    } else if (drow < 0) {
      for(i = 0; i >= drow; i--) { cursor_move_down(curs, row, target->id); }
    }

    if (dcol > 0) {
      for(i = 0; i >= dcol; i--) { cursor_move_right(curs, row); }
    } else if (dcol < 0) {
      for(i = 0; i <= dcol; i++) { cursor_move_left(curs, row); }
    }
  }
  return 1;
}
