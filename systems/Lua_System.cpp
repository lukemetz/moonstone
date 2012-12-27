#include "Lua_System.hpp"
#include <iostream>
#include "Manager.hpp"

Lua_System::Lua_System(lua_State * lua_state, std::string filename)
{
  L = lua_state;
  lua_settop(L, 0);
  int s = luaL_dofile(L, filename.c_str());
  report_errors(s);

  script_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  lua_rawgeti(L, LUA_REGISTRYINDEX, script_ref);

  lua_getfield(L, -1, "init");
  lua_pushvalue(L, -2); //push setlf
  s = lua_pcall(L, 1, 1, 0);
  report_errors(s);

  int n = lua_rawlen(L, -1);

  lua_pushnil(L);
  for (int i=0; i < n; i++) {
    lua_next(L, -2*i);
    const char * v = lua_tostring(L, -1);

    std::string component_name(v);
    components.push_back(component_name);
    lua_pop(L, 1);
  }
  lua_pop(L,1);

}

Lua_System::~Lua_System()
{
  lua_close(L);
}

lua_State * Lua_System::get_lua_state()
{
  return L;
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

void Lua_System::create_ref_vector()
{
  std::vector<int> entities = manager->get_entities(components);
  for(auto entity : entities) {
    lua_settop(L, 0);
    lua_newtable(L);
    for(std::string component_name : components) {
      Component * component = manager->get_component(entity, component_name);
      int ref = component->get_lua_ref(L);
      lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
      lua_setfield(L, -2, component_name.c_str());
    }
    int table_ref = luaL_ref(L, LUA_REGISTRYINDEX);
    entity_ref_vector[entity] = table_ref;
  }
  lua_settop(L, 0);
}

void Lua_System::replace_entity_ref(int entity)
{
  lua_rawgeti(L, LUA_REGISTRYINDEX, entity_ref_vector[entity]);

  for(std::string component_name : components) {
    Component * component = manager->get_component(entity, component_name);
    lua_getfield(L, -1, component_name.c_str());
    component->update_from_lua(L);
  }
}

void Lua_System::update(float dt)
{
  create_ref_vector();
  for(int entity : manager->get_entities(components)) {
    //reset the stack
    lua_settop(L, 0);
    lua_rawgeti(L, LUA_REGISTRYINDEX, script_ref);

    lua_getfield(L, -1, "update");
    lua_pushvalue(L, -2); //push setlf
    lua_pushnumber(L, dt);
    //push the entity
    lua_rawgeti(L, LUA_REGISTRYINDEX, entity_ref_vector[0]);

    int s = lua_pcall(L, 3, 0, 0);
    report_errors(s);

    //Re-populate components

    replace_entity_ref(entity);
    lua_pop(L,1);
  }
}
