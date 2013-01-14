#include "bindings.hpp"
#include <iostream>

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
