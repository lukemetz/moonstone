#pragma once
#include "/usr/local/include/luajit-2.0/lua.hpp"
#include "lua_compatibility.hpp"

#include "utils/Vec3f.hpp"
#include "utils/Quat.hpp"

class Lua_Manager;

class Lua_Manager
{
public:
  Lua_Manager();
  ~Lua_Manager();
  lua_State * get_lua_state();
  int to_lua_ref(const Vec3f &vec);
  void from_lua(Vec3f &vec);

  int to_lua_ref(const Quat &quat);
  void from_lua(Quat &quat);

  static Lua_Manager * get_instance();
  static Lua_Manager * instance;

  void report_errors(int status);
private:
  lua_State *L;
};

