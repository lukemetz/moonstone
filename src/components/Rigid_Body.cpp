#include "Rigid_Body.hpp"
#include "Lua_Manager.hpp"
#include "Collider.hpp"
#include <iostream>
#include "Manager.hpp"

Rigid_Body::Rigid_Body()
{
}

void Rigid_Body::get_Vec3f_bind(lua_State *L, Vec3f &vec, std::string name)
{
  int ref = Lua_Manager::get_instance()->to_lua_ref(vec);
  lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
  lua_setfield(L, -2, name.c_str());
}

void Rigid_Body::init_Vec3f_bind(lua_State *L, Vec3f &vec, std::string name)
{
  lua_getfield(L, -1, name.c_str());
  if(!lua_isnil(L, -1))
    Lua_Manager::get_instance()->from_lua(vec);
  lua_pop(L, 1);
}

void Rigid_Body::update_Vec3f_bind(lua_State *L, Vec3f &vec, std::string name)
{
  lua_getfield(L, -1, name.c_str());
  Lua_Manager::get_instance()->from_lua(vec);
  lua_pop(L, 1);
}

int Rigid_Body::get_lua_ref(lua_State * L)
{
  lua_newtable(L);
  lua_pushnumber(L, mass);
  lua_setfield(L, -2, "mass");

  lua_pushnumber(L, friction);
  lua_setfield(L, -2, "friction");

  get_Vec3f_bind(L, forces, "forces");
  
  get_Vec3f_bind(L, velocity, "velocity");

  get_Vec3f_bind(L, angular_factor, "angular_factor");
  get_Vec3f_bind(L, linear_factor, "linear_factor");

  return luaL_ref(L, LUA_REGISTRYINDEX);
}

void Rigid_Body::update_from_lua(lua_State * L)
{
  update_Vec3f_bind(L, forces, "forces");
  update_Vec3f_bind(L, velocity, "velocity");

  lua_getfield(L, -1, "mass");
  mass = lua_tonumber(L, -1);
  lua_pop(L, 1);

  lua_getfield(L, -1, "friction");
  friction = lua_tonumber(L, -1);
  lua_pop(L, 1);
 
  update_Vec3f_bind(L, angular_factor, "angular_factor");
  update_Vec3f_bind(L, linear_factor, "linear_factor");

}

void Rigid_Body::init_from_lua(lua_State * L)
{
  lua_getfield(L, -1, "mass");
  if(!lua_isnil(L, -1))
    mass = lua_tonumber(L, -1);
  lua_pop(L, 1);

  lua_getfield(L, -1, "friction");
  if(!lua_isnil(L, -1))
    friction = lua_tonumber(L, -1);
  lua_pop(L, 1);

  lua_getfield(L, -1, "linear_damping");
  if(!lua_isnil(L, -1))
    linear_damping = lua_tonumber(L, -1);
  lua_pop(L, 1);
  
  lua_getfield(L, -1, "angular_damping");
  if(!lua_isnil(L, -1))
    angular_damping = lua_tonumber(L, -1);
  lua_pop(L, 1);

  lua_getfield(L, -1, "friction");
  if(!lua_isnil(L, -1))
    friction = lua_tonumber(L, -1);
  lua_pop(L, 1);

  init_Vec3f_bind(L, offset, "offset");

  init_Vec3f_bind(L, linear_factor, "linear_factor");
  init_Vec3f_bind(L, angular_factor, "angular_factor");

  init_Vec3f_bind(L, forces, "forces");

  init_Vec3f_bind(L, velocity, "velocity");
  init_Vec3f_bind(L, torque, "torque");
}

void Rigid_Body::added_to_entity(Manager * manager, int entity)
{
  Collider * collider = static_cast<Collider *>(manager->get_component(entity, "Collider"));
  if (nullptr == collider) {
    std::cerr << "waiting" << std::endl; //Call this method from Collider
    return;
  }

  btTransform t = btTransform(btQuaternion(0,0,0,1), btVector3(offset.x, offset.y, offset.z));
  btDefaultMotionState * motion_state = new btDefaultMotionState(t);

  btCollisionShape * shape = collider->shape;

  btVector3 fall_inertia(0,0,0);
  if (mass != 0) {
    shape->calculateLocalInertia(mass, fall_inertia);
  }

  btRigidBody::btRigidBodyConstructionInfo
    construction_info(mass, motion_state, shape, fall_inertia);

  body = new btRigidBody(construction_info);
  body->setDamping(linear_damping, angular_damping);

  body->setFriction(friction);
  body->setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
  Bullet_Manager::get_instance()->add_rigid_body(body);
}

void Rigid_Body::remove()
{
  Bullet_Manager::get_instance()->remove_rigid_body(body);
  delete body->getMotionState();
  delete body;
  body = nullptr;
}
