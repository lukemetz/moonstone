#include "bindings.hpp"
#include <iostream>
#include "Component.hpp"
#include <string>
#include <vector>
#include <map>

void lua_setup_manager(lua_State *L, Manager * manager)
{
  lua_pushglobaltable(L);
  lua_createtable(L, 2, 0);

  lua_pushlightuserdata(L, static_cast<void *>(manager));
  lua_setfield(L, -2, "ptr");

  lua_pushcfunction(L, &lua_manager_pause);
  lua_setfield(L, -2, "pause");

  lua_pushcfunction(L, &lua_manager_resume);
  lua_setfield(L, -2, "resume");

  lua_pushcfunction(L, &lua_manager_get_all_entities);
  lua_setfield(L, -2, "get_all_entities");

  lua_pushcfunction(L, &lua_manager_update_all_entities);
  lua_setfield(L, -2, "update_all_entities");
  
  lua_pushcfunction(L, &lua_manager_get_component);
  lua_setfield(L, -2, "get_component");

  lua_setfield(L, -2, "manager");
  lua_pop(L, 1);
}

Manager * get_manager(lua_State *L)
{
  int argc = lua_gettop(L);
  if (argc < 1) {
    std::cerr << "No self paramater passed. Maybe try ':' vs '.'" << std::endl;

    return 0;
  }
  lua_getfield(L, 1, "ptr");
  Manager * manager = static_cast<Manager *>(lua_touserdata(L, -1));
  printf("%p \n", manager);
  return manager;
}

int lua_manager_pause(lua_State *L)
{
  printf("Paused\n");
  get_manager(L)->pause();
  return 0;
}

int lua_manager_resume(lua_State *L)
{
  printf("resumed\n");
  get_manager(L)->resume();
  return 0;
}

int lua_manager_get_all_entities(lua_State *L)
{
  Manager * manager = get_manager(L);
  std::vector<int> entities = manager->get_all_entities();
  lua_createtable(L, entities.size(), 0);
  int index = 1;
  for (int entity : entities) {
    std::map<std::string, Component *> map = manager->get_all_components_map(entity);
    lua_createtable(L, 0, 0); //create the entity table
    for (auto iter = map.begin(); iter != map.end(); ++iter) {
      int ref = iter->second->get_lua_ref(L);
      //Set each component by name
      lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
      lua_setfield(L, -2, iter->first.c_str());
    }
    lua_rawseti(L, -2, index++); //set the index of entity
  }
  return 1;
}

int lua_manager_update_all_entities(lua_State *L)
{
  Manager * manager = get_manager(L);
  std::vector<int> entities = manager->get_all_entities();
  lua_pushvalue(L, 2); // Push the first non self argument to -1
  lua_pushnil(L);
  while(lua_next(L, -2)) {
    int entity = lua_tonumber(L, -2);
    lua_pushnil(L);
    while(lua_next(L, -2)) {
      std::string component_name = lua_tostring(L, -2);
      Component * comp = manager->get_component(entity, component_name);
      comp->update_from_lua(L);
      lua_pop(L, 1);
    }
    lua_pop(L, 1);
  }
  lua_pop(L, 1);
  return 0;
}

int lua_manager_get_component(lua_State *L)
{
  Manager * manager = get_manager(L);
  int entity = static_cast<int>(lua_tonumber(L, 2));
  std::string component_name = lua_tostring(L, 3);

  Component * component = manager->get_component(entity, component_name);
  if (component == nullptr) {
    lua_pushnil(L);
  } else {
    lua_rawgeti(L, LUA_REGISTRYINDEX, component->get_lua_ref(L));
  }
  return 1;
}
