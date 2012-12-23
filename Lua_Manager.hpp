#include <lua5.2/lua.hpp>
#include "utils/Vec3f.hpp"

class Lua_Manager;

class Lua_Manager
{
public:
  Lua_Manager();
  ~Lua_Manager();
  lua_State * get_lua_state();
  int to_lua_ref(const Vec3f &vec);

  void from_lua(Vec3f &vec);

  static Lua_Manager * get_instance();
  static Lua_Manager * instance;
private:
  lua_State *L;
  void report_errors(int status);
};

