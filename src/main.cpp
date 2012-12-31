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
#include "register_systems.hpp"
#include "init_from_lua.hpp"
#include "OIS_Input_Manager.hpp"

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
  register_systems(manager);
  Lua_Manager *lua_man = new Lua_Manager();
  Ogre_Manager * ogre_manager = new Ogre_Manager(manager);
  OIS_Input_Manager * input_manager = new OIS_Input_Manager();
  ogre_manager->set_ois_input_manager(input_manager);
  ogre_manager->init();

  init_from_lua(manager, "lua/main.lua");

  try {
    ogre_manager->go();
  } catch( Ogre::Exception & e)  {
    std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
  }
  return 0;
}
