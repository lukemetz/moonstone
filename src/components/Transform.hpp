#pragma once

#include "Component.hpp"
#include "utils/Vec3f.hpp"
#include "utils/Quat.hpp"
struct Transform : public Component
{
  Vec3f pos;
  Quat rot;
  Vec3f scale = Vec3f(1,1,1);
  virtual std::string name() { return "Transform"; };
  virtual int get_lua_ref(lua_State * L);
  virtual void update_from_lua(lua_State * L);
};
