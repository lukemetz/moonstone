#pragma once

#include <string>
#include <vector>
#include <map>

#include "System.hpp"
#include "Lua_Manager.hpp"

struct Lua_System : public System
{
  Lua_System();
  void set_file(std::string filename);
  ~Lua_System();
  void init();
  void update(float dt);
  lua_State * get_lua_state();

  int create_entity_ref(int entity);
  void replace_entity_ref(int entity);

private:
  lua_State *L;
  int script_ref;
  std::string script_name;
  std::vector<std::string> components;
  std::map<int, int> entity_ref_vector;
  void create_ref_vector();
};
