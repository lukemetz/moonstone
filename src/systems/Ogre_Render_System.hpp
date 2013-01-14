#pragma once

#include "Ogre_Manager.hpp"
#include "System.hpp"

struct Ogre_Render_System : public System
{
public:

  Ogre_Render_System() {};
  Ogre_Manager * ogre_manager;
  virtual void init();
  virtual void update(float dt);
  virtual std::string get_name() {
    return "Ogre_Render_System";
  }
};
