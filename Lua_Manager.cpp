#include "Lua_Manager.hpp"
#include <iostream>

Lua_Manager * Lua_Manager::instance = nullptr;

Lua_Manager::Lua_Manager()
{
  L = luaL_newstate();
  luaL_openlibs(L);
  luaL_dofile(L, "lua/utils/Vec3f.lua");
  instance = this;
}

Lua_Manager::~Lua_Manager()
{
  lua_close(L);
}

Lua_Manager * Lua_Manager::get_instance()
{
  return instance;
}

void Lua_Manager::report_errors(int status)
{
  if (status != 0 ) {
    std::cerr << "Lua Error #" << status << ":" << lua_tostring(L, -1) << std::endl;
    lua_pop(L, 1);
    if (status == 1) {
      std::cout << "No c++ or lua file found" << std::endl;
      exit(1);
    }
  }
}

lua_State * Lua_Manager::get_lua_state()
{
  return L;
}

int Lua_Manager::to_lua_ref(const Vec3f &vec)
{
  lua_getglobal(L, "Vec3f");
  lua_pushnumber(L, vec.x);
  lua_pushnumber(L, vec.y);
  lua_pushnumber(L, vec.z);

  int s = lua_pcall(L, 3, 1, 0);
  report_errors(s);

  int ref = luaL_ref(L, LUA_REGISTRYINDEX);
  return ref;
}

void Lua_Manager::from_lua(Vec3f &vec)
{
  lua_getfield(L, -1, "x");
  vec.x = lua_tonumber(L, -1);
  lua_pop(L, 1);

  lua_getfield(L, -1, "y");
  vec.y = lua_tonumber(L, -1);
  lua_pop(L, 1);

  lua_getfield(L, -1, "z");
  vec.z = lua_tonumber(L, -1);
  lua_pop(L, 1);
}
