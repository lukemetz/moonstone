#include "Light.hpp"
#include "Ogre_Manager.hpp"

Light::Light()
{
  light = Ogre_Manager::get_instance()->scene_mgr->createLight();
}


int Light::get_lua_ref(lua_State * L)
{
  lua_newtable(L);
  return luaL_ref(L, LUA_REGISTRYINDEX);
}

void Light::update_from_lua(lua_State * L)
{
}

void Light::init_from_lua(lua_State * L)
{
}

void Light::remove()
{
  Ogre_Manager::get_instance()->scene_mgr->destroyLight(light);
}
