#include "Lua_Manager.hpp"

Lua_Manager::Lua_Manager()
{
  L = luaL_newstate();
  luaL_openlibs(L);
}

Lua_Manager::~Lua_Manager()
{
  lua_close(L);
}

lua_State * Lua_Manager::get_lua_state()
{
  return L;
}
