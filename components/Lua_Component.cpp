#include "Lua_Component.hpp"
#include "utils/string.hpp"
#include "Lua_Manager.hpp"
#include <iostream>

Lua_Component::Lua_Component()
{
  component_ref = LUA_REFNIL;
  component_name = "Lua_Undefined";
}

void Lua_Component::set_file(std::string filename)
{
  L = Lua_Manager::get_instance()->get_lua_state();

  int s = luaL_dofile(L, filename.c_str());
  report_errors(s);
  component_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  lua_pop(L, 1);

  std::vector<std::string> strings = split(filename, '/');
  component_name = split(strings.back(), '.')[0];
}

void Lua_Component::report_errors(int status)
{
  if (status != 0 ) {
    std::cerr << "ERROR-- " << lua_tostring(L, -1) << std::endl;
    lua_pop(L, 1);
  }
}

int Lua_Component::get_lua_ref(lua_State * L)
{
  return component_ref;
}

std::string Lua_Component::name()
{
  return component_name;
}
