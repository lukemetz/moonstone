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
  lua_pushvalue(L, -1);
  component_ref = luaL_ref(L, LUA_REGISTRYINDEX);
}
