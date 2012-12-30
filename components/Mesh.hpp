#pragma once
#include "Component.hpp"

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include "Ogre_Manager.hpp"

struct Mesh : public Component
{
  Mesh();
  void set_file(std::string filename);
  virtual std::string name() { return "Mesh"; };
  virtual int get_lua_ref(lua_State * L);
  virtual void update_from_lua(lua_State * L);

  Ogre::Entity * entity;
  Ogre::SceneNode * scene_node;

  virtual void init_from_lua(lua_State * L);
};
