#pragma once

#include <lua5.2/lua.hpp>
#include <string>
#include <vector>

#include "Component.hpp"

struct Lua_Component : public Component
{
  Lua_Component(lua_State *lua_state, std::string filename);
  virtual std::string name();
  virtual int get_lua_ref(lua_State * L);
private:
  std::string component_name;
  int component_ref;
  lua_State * L;
  void report_errors(int status);
};
