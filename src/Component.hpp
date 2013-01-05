#pragma once

#include <string>
#include "Lua_Manager.hpp"

class Manager;

struct Component
{
  virtual std::string name() {return "Hello";};
  virtual int get_lua_ref(lua_State * L) {return LUA_REFNIL;};
  virtual void update_from_lua(lua_State * L) {};

  virtual void init_from_lua(lua_State * L) {update_from_lua(L);}
  virtual void added_to_entity(Manager * manager, int entity) {}
};
