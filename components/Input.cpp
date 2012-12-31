#include "Input.hpp"
#include "Lua_Manager.hpp"

int Input::get_lua_ref(lua_State * L)
{
  lua_newtable(L);

  int ref = luaL_ref(L, LUA_REGISTRYINDEX);
  return ref;
}

void Input::update_from_lua(lua_State * L)
{
}
