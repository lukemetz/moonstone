#include "Lua_Manager.hpp"
#include "Manager.hpp"

void lua_setup_manager(lua_State *L, Manager * manager);
//Call like manager:pause()
int lua_manager_pause(lua_State *L);
//Call like manager:resume()
int lua_manager_resume(lua_State *L);
//Call like entities = manager:get_all_entities()
int lua_manager_get_all_entities(lua_State *L);
//Call like manager:update_all_entities(entities)
int lua_manager_update_all_entities(lua_State *L);
//Call like manager:get_component(entity, "Component_name")
int lua_manager_get_component(lua_State *L);
//Call like size = manager:get_frame_size()
int lua_manager_get_frame_size(lua_State *L);

