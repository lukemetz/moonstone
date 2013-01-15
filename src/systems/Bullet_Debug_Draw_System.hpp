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
  virtual void remove();
  virtual void update(float dt);
  virtual std::string get_name() {
    return "Bullet_Debug_Draw_System";
  }

  BtOgre::DebugDrawer * debug_drawer = nullptr;
};
