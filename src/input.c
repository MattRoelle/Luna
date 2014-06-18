#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "input.h"
#include "state.h"
#include "types.h"
#include "LUA.h"

luna get_input() {
  char c = getch();
  push_input(c);
  return SUCCESS;
}

luna push_input(char c) {
  int i;
  for(i = 30; i >= 0; i--) {
    input_buffer[i + 1] = input_buffer[i];
  }
  input_buffer[0] = c;

  lua_pushstring(L, input_buffer);
  lua_setglobal(L, "input_buffer");

  return SUCCESS;
}

char* read_input(char len) {
  char *buffer = malloc(len * sizeof(char));
  strncpy(buffer, input_buffer, len);
  return buffer;
}
