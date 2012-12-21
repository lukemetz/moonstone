#include "Lua_System.hpp"
#include <iostream>
Lua_System::Lua_System()
{
  L = luaL_newstate();
  luaL_openlibs(L);

  lua_newtable(L);
  systems_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  lua_pop(L, 1);
}

Lua_System::~Lua_System()
{
  lua_close(L);
}

void Lua_System::init()
{
}

void Lua_System::report_errors(int status)
{
  if (status != 0 ) {
    std::cerr << "ERROR-- " << lua_tostring(L, -1) << std::endl;
    lua_pop(L, 1);
  }
}

void Lua_System::add_system(std::string filename)
{
  lua_rawgeti(L, LUA_REGISTRYINDEX, systems_ref);
  int s = luaL_dofile(L, filename.c_str());
  report_errors(s);
  lua_setfield(L, -2, filename.c_str());
  lua_pop(L, 1);

  scripts.push_back(filename);
}

void Lua_System::update(float dt)
{
  lua_rawgeti(L, LUA_REGISTRYINDEX, systems_ref);
  for(std::string script : scripts) {
    lua_getfield(L, -1, "lua_system.lua");

    lua_getfield(L, -1, "update");
    lua_pushvalue(L, -2); //push setlf
    lua_pushnumber(L, dt);
    int s = lua_pcall(L, 2, 0, 0);
    report_errors(s);
    lua_pop(L,1);
  }
}
