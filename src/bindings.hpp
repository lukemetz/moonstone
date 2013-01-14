#include "Lua_Manager.hpp"
#include "Manager.hpp"

void lua_setup_manager(lua_State *L, Manager * manager);
int lua_manager_pause(lua_State *L);
int lua_manager_resume(lua_State *L);
