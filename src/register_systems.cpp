#include "register_systems.hpp"
#include "Manager.hpp"

#include "systems/Ogre_Render_System.hpp"
#include "systems/Lua_System.hpp"
#include "systems/OIS_Input_System.hpp"
#include "systems/Bullet_Debug_Draw_System.hpp"
#include "systems/Bullet_System.hpp"

void register_systems(Manager * manager)
{
  manager->register_system<Ogre_Render_System>("Ogre_Render_System");
  manager->register_system<Lua_System>("Lua_System");
  manager->register_system<OIS_Input_System>("OIS_Input_System");
  manager->register_system<Bullet_Debug_Draw_System>("Bullet_Debug_Draw_System");
  manager->register_system<Bullet_System>("Bullet_System");
}
