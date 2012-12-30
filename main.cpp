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
#include "register_components.hpp"

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
  register_components(manager);
  Lua_Manager *lua_man = new Lua_Manager();
  Test_System * sys = new Test_System();
  //manager->add_system(sys);

  Lua_System * lua_sys = new Lua_System(lua_man->get_lua_state(), "lua/systems/lua_system.lua");
  //for(int i=0; i < 200; i++)
  manager->add_system(lua_sys);

  //Start up the ogre loop
  Ogre_Manager * ogre_manager = new Ogre_Manager(manager);
  ogre_manager->init();

  Ogre_Render_System * render_system = new Ogre_Render_System(ogre_manager);
  manager->add_system(render_system);

  int camera = manager->createEntity();
  manager->add_component(camera, manager->create_component("Camera"));

  int ogre = manager->createEntity();
  manager->add_component(ogre, manager->create_component("Transform"));
  Mesh * mesh =  (Mesh *)manager->create_component("Mesh");
  mesh->set_file("ogrehead.mesh");
  manager->add_component(ogre, mesh);

  Lua_Component * lua_comp = (Lua_Component *)manager->create_component("lua_component");
  lua_comp->set_file("lua/components/lua_component.lua");
  manager->add_component(ogre, lua_comp);




  try {
    ogre_manager->go();
  } catch( Ogre::Exception & e)  {
    std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
  }
  return 0;
}
