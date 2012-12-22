#include <lua5.2/lua.hpp>

class Lua_Manager
{
public:
  Lua_Manager();
  ~Lua_Manager();
  lua_State * get_lua_state();
private:
  lua_State *L;
};
