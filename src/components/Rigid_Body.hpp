#pragma once
#include "Component.hpp"
#include "utils/Vec3f.hpp"

#include "Bullet_Manager.hpp"
#include <btBulletDynamicsCommon.h>

struct Rigid_Body : public Component
{
  Rigid_Body();

  virtual std::string name() { return "Rigid_Body"; };
  virtual int get_lua_ref(lua_State * L);
  virtual void update_from_lua(lua_State * L);
  virtual void init_from_lua(lua_State * L);
  virtual void added_to_entity(Manager * manager, int entity);
  virtual void remove();

  btRigidBody * body = nullptr;
  Vec3f offset;
  float mass = 0;
  float friction = 0;
  Vec3f forces = Vec3f(0,0,0);
  Vec3f torque = Vec3f(0,0,0);
  Vec3f velocity = Vec3f(0,0,0);
  Vec3f angular_velocity = Vec3f(0,0,0);
  float linear_damping = 0;
  float angular_damping = 0;
  Vec3f angular_factor = Vec3f(1,1,1);
  Vec3f linear_factor = Vec3f(1,1,1);
  //Protected
  int on_step = 0;

protected:
  void get_Vec3f_bind(lua_State *L, Vec3f &vec, std::string name);
  void init_Vec3f_bind(lua_State *L, Vec3f &vec, std::string name);
  void update_Vec3f_bind(lua_State *L, Vec3f &vec, std::string name);
};
