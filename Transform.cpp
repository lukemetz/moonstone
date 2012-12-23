#include "Transform.hpp"
#include "Lua_Manager.hpp"

int Transform::get_lua_ref(lua_State * L)
{
  lua_newtable(L);
  lua_newtable(L);
  int pos_ref = Lua_Manager::get_instance()->to_lua_ref(pos);
  lua_rawgeti(L, LUA_REGISTRYINDEX, pos_ref);
  lua_setfield(L, -2, "pos");

  int rot_ref = Lua_Manager::get_instance()->to_lua_ref(rot);
  lua_rawgeti(L, LUA_REGISTRYINDEX, rot_ref);
  lua_setfield(L, -2, "rot");

  int scale_ref = Lua_Manager::get_instance()->to_lua_ref(scale);
  lua_rawgeti(L, LUA_REGISTRYINDEX, scale_ref);
  lua_setfield(L, -2, "scale");

  int ref = luaL_ref(L, LUA_REGISTRYINDEX);
  return ref;
}
