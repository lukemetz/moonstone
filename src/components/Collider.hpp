#pragma once
#include "Component.hpp"
#include "utils/Vec3f.hpp"

#include "Bullet_Manager.hpp"
#include <btBulletDynamicsCommon.h>

struct Collider : public Component
{
  Collider();

  virtual std::string name() { return "Collider"; };
  virtual int get_lua_ref(lua_State * L);
  virtual void update_from_lua(lua_State * L);
  virtual void init_from_lua(lua_State * L);

  void set_sphere_shape(float radius);
  void set_box_shape(const Vec3f & half_side);

  std::string type = "";
  btCollisionShape * shape = nullptr;
};
