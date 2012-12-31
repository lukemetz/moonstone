#include "init_from_lua.hpp"
#include "Manager.hpp"
#include "Lua_Manager.hpp"
#include <iostream>

void setup_systems(lua_State * L, Manager * manager)
{
  //lua_pushglobaltable(L);
  lua_getfield(L, -1, "systems");
  std::cout << "istable?" << lua_istable(L, -1) << std::endl;
  std::cout << "got_sys" << std::endl;

  int n = lua_rawlen(L, -1);
  lua_pushnil(L);
  while(lua_next(L, -2)) {
    std::string name = lua_tostring(L, -1);
    std::cout << "Found system:" << name << std::endl;
    System * s = manager->create_system(name);
    manager->add_system(s);
    lua_pop(L, 1);
  }
  lua_pop(L, 1);
}

void setup_components(lua_State * L, Manager * manager)
{
  lua_pushglobaltable(L);
  lua_getfield(L, -1, "entities");
  std::cout << "istable?" << lua_istable(L, -1) << std::endl;
  std::cout << "got_sys" << std::endl;

  int n = lua_rawlen(L, -1);
  lua_pushnil(L);
  for (int i=0; i < n; i++) {
    lua_next(L, -2);
    int entity = manager->createEntity();
      lua_pushnil(L);  /* first key */
      while (lua_next(L, -2) != 0) {
        /* uses 'key' (at index -2) and 'value' (at index -1) */
        std::string component_name = lua_tostring(L,-2);
        printf("Adding %s on entity %d \n", component_name.c_str(), entity);
        Component * c = manager->create_component(component_name);
        c->init_from_lua(L);
        manager->add_component(entity, c);
        lua_pop(L, 1); // remove the value but keep the key
      }
    lua_pop(L, 1);
  }
  lua_pop(L, 1);
}

void init_from_lua(Manager *manager, std::string filename)
{
  lua_State * L = Lua_Manager::get_instance()->get_lua_state();
  int s = luaL_dofile(L, filename.c_str());
  Lua_Manager::get_instance()->report_errors(s);
  lua_pushglobaltable(L);
  setup_systems(L, manager);
  setup_components(L, manager);
}
