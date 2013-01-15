#pragma once

#include <string>
#include <vector>

#include "Component.hpp"

struct Lua_Component : public Component
{
  Lua_Component();
  void set_name(std::string name);
  virtual std::string name();
  virtual int get_lua_ref(lua_State * L);
  virtual void remove();
  void init_from_lua(lua_State * L);

protected:
  std::string component_name;
  int component_ref;
  lua_State * L;
};
