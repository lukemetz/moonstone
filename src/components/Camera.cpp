#include "Camera.hpp"

int Camera::get_lua_ref(lua_State * L)
{
  lua_newtable(L);
  return luaL_ref(L, LUA_REGISTRYINDEX);
}

void Camera::update_from_lua(lua_State * L)
{
  lua_getfield(L, -1, "near_clip");
  near_clip = lua_tonumber(L, -1);
  lua_pop(L, 1);
}

void Camera::init_from_lua(lua_State * L)
{
  lua_getfield(L, -1, "near_clip");
  if(!lua_isnil(L, -1))
    near_clip = lua_tonumber(L, -1);
  lua_pop(L, 1);
}
