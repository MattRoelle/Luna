#ifndef LUA_H
#define LUA_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "types.h"

lua_State *L;

luna init_LUA();
luna end_LUA();
luna register_luna_functions();

// Functions that are exposed to LUA
int l_print(lua_State *);
int l_switch_state(lua_State *);
int l_get_state(lua_State *);
int l_switch_buffer(lua_State *);
int l_move_cursor(lua_State *);

#endif
