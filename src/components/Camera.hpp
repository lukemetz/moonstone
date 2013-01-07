#pragma once
#include "Component.hpp"

struct Camera : public Component
{
  virtual std::string name() { return "Camera"; };
  virtual int get_lua_ref(lua_State * L);
  virtual void update_from_lua(lua_State * L);
  virtual void init_from_lua(lua_State * L);

  float near_clip = 1;
};
