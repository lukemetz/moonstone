#include "Collider.hpp"
#include "Lua_Manager.hpp"

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
  type = lua_tostring(L, -1);
  lua_pop(L, 1);

  if (type == "sphere") {
    lua_getfield(L, -1, "radius");
    float radius = lua_tonumber(L, -1);
    set_sphere_shape(radius);
    lua_pop(L, 1);
  } else if(type == "box") {
    Vec3f width;
    lua_getfield(L, -1, "side");
    Lua_Manager::get_instance()->from_lua(width);
    set_box_shape(width/2);
    lua_pop(L, 1);
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
