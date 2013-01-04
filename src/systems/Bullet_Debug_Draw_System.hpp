#pragma once

#include "Bullet_Manager.hpp"
#include "Ogre_Manager.hpp"
#include "System.hpp"

#include "externals/btogre/BtOgreExtras.h"

struct Bullet_Debug_Draw_System : public System
{
public:
  Ogre_Manager * ogre_manager = nullptr;
  Bullet_Manager * bullet_manager = nullptr;
  Bullet_Debug_Draw_System() {};
  virtual void init();
  virtual void update(float dt);

  BtOgre::DebugDrawer * debug_drawer = nullptr;
};
