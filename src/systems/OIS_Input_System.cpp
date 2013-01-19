#include "OIS_Input_System.hpp"
#include "OIS_Input_Manager.hpp"
#include "Manager.hpp"
#include "components/Input.hpp"
#include "Lua_Manager.hpp"

#include <iostream>

const int num_keys = 222;
const int num_mouse = 8;

OIS_Input_System::OIS_Input_System()
{
  keys = (bool *)calloc(num_keys, sizeof(bool));
  mouse = (bool *)calloc(num_mouse, sizeof(bool));
  mouse_dx = (int *)calloc(1, sizeof(int));
  mouse_dy = (int *)calloc(1, sizeof(int));
  mouse_x = (int *)calloc(1, sizeof(int));
  mouse_y = (int *)calloc(1, sizeof(int));
}

OIS_Input_System::~OIS_Input_System()
{
  delete keys, mouse, mouse_dx, mouse_dy;
}

void OIS_Input_System::init()
{
  lua_State * L = Lua_Manager::get_instance()->get_lua_state();
  lua_pushglobaltable(L);
  lua_createtable(L, num_keys, 0);
  for (int i=0; i < num_keys; ++i) {
    lua_pushboolean(L, false);
    lua_rawseti(L, -2, i);
  }
  lua_setfield(L, -2, "keys");

  lua_createtable(L, num_mouse, 0);
  for (int i=0; i < num_mouse; ++i) {
    lua_pushboolean(L, false);
    lua_rawseti(L, -2, i);
  }
  lua_setfield(L, -2, "mouse");

  lua_pushnumber(L, 0);
  lua_setfield(L, -2, "mouse_x");

  lua_pushnumber(L, 0);
  lua_setfield(L, -2, "mouse_y");
  
  lua_pushnumber(L, 0);
  lua_setfield(L, -2, "mouse_dx");

  lua_pushnumber(L, 0);
  lua_setfield(L, -2, "mouse_dy");

  lua_setfield(L, -1, "__input");
  lua_pop(L, 1);

  lua_pushglobaltable(L);
  lua_getfield(L, -1, "__input");
  input_ref = luaL_ref(L, LUA_REGISTRYINDEX);
}

void OIS_Input_System::update(float dt)
{
  OIS_Input_Manager::get_instance()->populate_inputs(keys, mouse,
      mouse_dx, mouse_dy,
      mouse_x, mouse_y);

  std::vector<int> entities = manager->get_entities("Input");
  for(int entity : entities) {
    Input * i = (Input *)manager->get_component(entity, "Input");
    i->keys = keys;
    i->mouse = mouse;
    i->mouse_dx = mouse_dx;
    i->mouse_dy = mouse_dy;
    i->mouse_x = mouse_x;
    i->mouse_y = mouse_y;
  }
  update_lua();
}

void OIS_Input_System::update_lua()
{
  lua_State * L = Lua_Manager::get_instance()->get_lua_state();
  lua_rawgeti(L, LUA_REGISTRYINDEX, input_ref);

  lua_getfield(L, -1, "keys");
  for (int i=0; i < num_keys; ++i) {
    lua_pushboolean(L, keys[i]);
    lua_rawseti(L, -2, i);
  }
  lua_pop(L, 1);

  lua_getfield(L, -1, "mouse");
  for (int i=0; i < num_mouse; ++i) {
    lua_pushboolean(L, mouse[i]);
    lua_rawseti(L, -2, i);
  }
  lua_pop(L, 1);

  lua_pushnumber(L, *mouse_dx);
  lua_setfield(L, -2, "mouse_dx");

  lua_pushnumber(L, *mouse_dy);
  lua_setfield(L, -2, "mouse_dy");

  lua_pushnumber(L, *mouse_x);
  lua_setfield(L, -2, "mouse_x");

  lua_pushnumber(L, *mouse_y);
  lua_setfield(L, -2, "mouse_y");
}
