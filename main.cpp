#include <iostream>
#include <stdio.h>
#include <cassert>
#include "utils/Vec3f.hpp"
#include "Manager.hpp"
#include "components/Transform.hpp"
#include "systems/Test_System.hpp"
#include "systems/Lua_System.hpp"
#include "components/Lua_Component.hpp"
#include "components/Camera.hpp"
#include "Lua_Manager.hpp"
#include "Ogre_Manager.hpp"
#include "systems/Ogre_Render_System.hpp"
#include "components/Mesh.hpp"

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
  //manager->add_component(index, comp);

  Camera * camera = new Camera();
  manager->add_component(index, camera);

  Test_System * sys = new Test_System();
  //manager->add_system(sys);

  Lua_System * lua_sys = new Lua_System(lua_man->get_lua_state(), "lua/systems/lua_system.lua");
  //for(int i=0; i < 200; i++)
  manager->add_system(lua_sys);

  Lua_Component * lua_comp = new Lua_Component(lua_man->get_lua_state(), "lua/components/lua_component.lua");


  std::vector<std::string> components;
  components.push_back("lua_component");
  components.push_back("Transform");
  std::vector<int > entities = manager->get_entities(components);
  std::cout << entities.size() << " out out" << std::endl;

  //Start up the ogre loop
  Ogre_Manager * ogre_manager = new Ogre_Manager(manager);
  ogre_manager->init();

  Ogre_Render_System * render_system = new Ogre_Render_System(ogre_manager);
  manager->add_system(render_system);

  //Create the ogre head
  Mesh * mesh = new Mesh(ogre_manager, "ogrehead.mesh");
  Transform * transform = new Transform();

  int ogre = manager->createEntity();

  manager->add_component(ogre, lua_comp);
  manager->add_component(ogre, mesh);
  manager->add_component(ogre, transform);

  try {
    ogre_manager->go();
  } catch( Ogre::Exception & e)  {
    std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
  }
  return 0;
}
