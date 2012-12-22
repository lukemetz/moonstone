#pragma once

#include <string>
#include <lua5.2/lua.hpp>

struct Component
{
  virtual std::string name() {return "Hello";};
  virtual int get_lua_ref(lua_State * L) {return LUA_REFNIL;};
};

