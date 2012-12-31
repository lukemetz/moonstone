#include "Camera.hpp"

int Camera::get_lua_ref(lua_State * L)
{
  lua_newtable(L);
  return luaL_ref(L, LUA_REGISTRYINDEX);
}

void Camera::update_from_lua(lua_State * L)
{

}
