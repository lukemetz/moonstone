#include <iostream>
#include <stdio.h>
#include <cassert>
#include "utils/Vec3f.hpp"
#include "Manager.hpp"
#include "Transform.hpp"
#include "Test_System.hpp"
#include "Lua_System.hpp"
#include "Lua_Component.hpp"
#include "Lua_Manager.hpp"
#include "Ogre_Manager.hpp"

#include <OgreException.h>

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
  Lua_Manager *lua_man = new Lua_Manager();
  int index = manager->createEntity();

  Transform *comp = new Transform();
  manager->add_component(index, comp);
  Vec3f t = Vec3f(1,2,3);
  comp->pos = t;
  comp->rot = Vec3f(1.2, 3.2, 3.3);

  Test_System * sys = new Test_System();
  manager->add_system(sys);


  Lua_System * lua_sys = new Lua_System(lua_man->get_lua_state(), "lua_system.lua");
  manager->add_system(lua_sys);

  Lua_Component * lua_comp = new Lua_Component(lua_man->get_lua_state(), "lua_component.lua");
  manager->add_component(index, lua_comp);


  std::vector<std::string> components;
  components.push_back("lua_component");
  components.push_back("Transform");
  std::vector<int > entities = manager->get_entities(components);
  std::cout << entities.size() << " out out" << std::endl;

  int ref = lua_man->to_lua_ref(Vec3f(1.11,4.44,3.33));
  std::cout << "found ref:" << ref << std::endl;
  lua_State *L = Lua_Manager::get_instance()->get_lua_state();
  lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
  lua_getfield(L, -1, "z");
  std::cout << "NEW!! Val for x::" << lua_tostring(L, -1) << std::endl;

  //Start up the ogre loop
  Ogre_Manager ogre_manager;

  try {
    ogre_manager.go();
  } catch( Ogre::Exception & e)  {
    std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
  }
  return 0;
}
