#include <lua5.2/lua.hpp>
#include <string>
#include <vector>

#include "System.hpp"

struct Lua_System : public System
{
  Lua_System();
  ~Lua_System();
  void init();
  void update(float dt);
  void add_system(std::string filename);

private:
  lua_State *L;
  int systems_ref;
  std::vector<std::string> scripts;
  void report_errors(int status);
};
