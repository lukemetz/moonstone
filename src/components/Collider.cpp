#include "Collider.hpp"
#include "Lua_Manager.hpp"
#include "Rigid_Body.hpp"
#include "Manager.hpp"

Collider::Collider()
{
}

int Collider::get_lua_ref(lua_State * L)
{
  lua_newtable(L);

  return luaL_ref(L, LUA_REGISTRYINDEX);
}

void Collider::update_from_lua(lua_State * L)
{

}

void Collider::init_from_lua(lua_State * L)
{
  lua_getfield(L, -1, "type");
  if (!lua_isnil(L, -1)) {
    type = lua_tostring(L, -1);
  } else {
    type = "sphere";
  }
  lua_pop(L, 1);

  if (type == "sphere") {
    float radius = 1;
    lua_getfield(L, -1, "radius");
    if (!lua_isnil(L, -1))
      radius = lua_tonumber(L, -1);
    lua_pop(L, 1);

    set_sphere_shape(radius);
  } else if(type == "box") {
    Vec3f width(2,2,2);
    lua_getfield(L, -1, "side");
    if (!lua_isnil(L, -1))
      Lua_Manager::get_instance()->from_lua(width);

    lua_pop(L, 1);
    set_box_shape(width/2);
  }
}

void Collider::added_to_entity(Manager * manager, int entity)
{
  //Small hack here, try to init the rigid body
  //again to make up for order of adding
  Rigid_Body * r =static_cast<Rigid_Body *>(manager->get_component(entity, "Rigid_Body"));
  if (r != nullptr) {
    r->added_to_entity(manager, entity);
  }
}

void Collider::set_sphere_shape(float radius)
{
  if (shape)
    delete shape;
  shape = new btSphereShape(radius);
}

void Collider::set_box_shape(const Vec3f & half_side)
{
  if (shape)
    delete shape;
  shape = new btBoxShape(btVector3(half_side.x, half_side.y, half_side.z));
}
