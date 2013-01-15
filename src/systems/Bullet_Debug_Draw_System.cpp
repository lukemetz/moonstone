#include "Bullet_Debug_Draw_System.hpp"
#include "Manager.hpp"
#include "components/Transform.hpp"
#include "components/Mesh.hpp"

void Bullet_Debug_Draw_System::init()
{
  bullet_manager = Bullet_Manager::get_instance();
  ogre_manager= Ogre_Manager::get_instance();

  debug_drawer =
    new BtOgre::DebugDrawer(ogre_manager->scene_mgr->getRootSceneNode(),
      bullet_manager->dynamics_world);

  bullet_manager->dynamics_world->setDebugDrawer(debug_drawer);
}

void Bullet_Debug_Draw_System::update(float dt)
{
  debug_drawer->step();
}
void Bullet_Debug_Draw_System::remove()
{
  bullet_manager->dynamics_world->setDebugDrawer(nullptr);
  delete debug_drawer;
}
