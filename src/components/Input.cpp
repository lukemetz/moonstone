#include "Input.hpp"
#include "Lua_Manager.hpp"

int Input::get_lua_ref(lua_State * L)
{
  lua_pushglobaltable(L);
  lua_getfield(L, -1, "__input");
  int ref = luaL_ref(L, LUA_REGISTRYINDEX);
  lua_pop(L, 1);
  return ref;
}

void Input::update_from_lua(lua_State * L)
{
}
