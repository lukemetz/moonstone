#pragma once

#include <lua5.2/lua.hpp>
#include <string>
#include <vector>
#include <map>

#include "System.hpp"

struct Lua_System : public System
{
  Lua_System(lua_State * lua_state, std::string filename);
  ~Lua_System();
  void init();
  void update(float dt);
  lua_State * get_lua_state();


private:
  lua_State *L;
  int script_ref;
  std::string script_name;
  std::vector<std::string> components;
  std::map<int, int> entity_ref_vector;

  void report_errors(int status);
  void create_ref_vector();
};
