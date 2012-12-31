#pragma once

#include "Component.hpp"

struct Input : public Component
{
  bool *modifiers = nullptr;
  bool *keys = nullptr;
  bool *mouse = nullptr;
  int *mouse_dx = nullptr;
  int *mouse_dy = nullptr;

  virtual std::string name() { return "Input"; };
  virtual int get_lua_ref(lua_State * L);
  virtual void update_from_lua(lua_State * L);
};
