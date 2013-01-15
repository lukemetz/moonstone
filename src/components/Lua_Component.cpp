#include "Lua_Component.hpp"
#include "utils/string.hpp"
#include "Lua_Manager.hpp"
#include <iostream>

Lua_Component::Lua_Component()
{
  component_ref = LUA_REFNIL;
  component_name = "Lua_Undefined";
}

void Lua_Component::set_name(std::string name)
{
  component_name = name;
}

int Lua_Component::get_lua_ref(lua_State * L)
{
  return component_ref;
}

std::string Lua_Component::name()
{
  return component_name;
}

void Lua_Component::init_from_lua(lua_State * L)
{
  //Deep copy and then store
  lua_pushglobaltable(L);
  lua_getfield(L, -1, "deepcopy");
  lua_remove(L, -2);
  lua_pushvalue(L, -2);
  int s = lua_pcall(L, 1, 1, 0);
  Lua_Manager::get_instance()->report_errors(s);
  component_ref = luaL_ref(L, LUA_REGISTRYINDEX);
}

void Lua_Component::remove()
{
  //luaL_unref(L, LUA_REGISTRYINDEX, component_ref);
  component_ref = LUA_REFNIL;
}
