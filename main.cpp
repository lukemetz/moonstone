#include <iostream>
#include <stdio.h>
#include <cassert>
#include "utils/Vec3f.hpp"
#include "Manager.hpp"
#include "Transform.hpp"
#include "Test_System.hpp"
#include "Lua_System.hpp"
#include "Lua_Component.hpp"

void report_errors(lua_State *L, int status)
{
  if (status != 0 ) {
    std::cerr << "ERROR-- " << lua_tostring(L, -1) << std::endl;
    lua_pop(L, 1);
  }
}

int main()
{
  Manager *manager = new Manager();
  int index = manager->createEntity();
  Transform *comp = new Transform();
  manager->add_component(index, comp);
  Vec3f t = Vec3f(1,2,3);
  comp->pos = t;
  comp->rot = Vec3f(1.2, 3.2, 3.3);

  Test_System * sys = new Test_System();
  manager->add_system(sys);
  Lua_System * lua_sys = new Lua_System();
  manager->add_system(lua_sys);
  lua_sys->add_system("lua_system.lua");
  lua_sys->add_system("lua_system.lua");
  lua_sys->add_system("lua_system.lua");

  Lua_Component * lua_comp = new Lua_Component(lua_sys->get_lua_state(), "lua_component.lua");
  manager->add_component(index, lua_comp);

  std::vector<int > entities = manager->get_entities("lua_component");
  std::cout << entities.size() << " out out" << std::endl;
  manager->update(1.1);
  return 0;
}
