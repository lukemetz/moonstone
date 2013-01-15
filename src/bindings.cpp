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
  int index = 0;
  for (int entity : entities) {
    std::cout << "Entity:" << entity << std::endl;
    std::map<std::string, Component *> map = manager->get_all_components_map(entity);
    lua_createtable(L, 0, 0); //create the entity table
    for (auto iter = map.begin(); iter != map.end(); ++iter) {
      int ref = iter->second->get_lua_ref(L);
      //Set each component by name
      lua_rawgeti(L, LUA_REGISTRYINDEX, ref); 
      lua_setfield(L, -2, iter->first.c_str());
      std::cout << "    " << iter->first << std::endl;
    }
    lua_rawseti(L, -2, index++); //set the index of entity
  }
  return 1;
}
