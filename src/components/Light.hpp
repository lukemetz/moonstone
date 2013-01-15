#pragma once
#include "Component.hpp"

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include "Ogre_Manager.hpp"

struct Light : public Component
{
  Light();
  virtual std::string name() { return "Light"; };
  virtual int get_lua_ref(lua_State * L);
  virtual void update_from_lua(lua_State * L);
  virtual void init_from_lua(lua_State * L);
  virtual void remove();

  Ogre::Light* light;
};
