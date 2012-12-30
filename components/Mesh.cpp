#include "Mesh.hpp"

Mesh::Mesh(Ogre_Manager * ogre_manager, std::string filename)
{
  entity = nullptr;
  scene_node = nullptr;
  try {
    entity = ogre_manager->scene_mgr->createEntity(filename);
    scene_node = ogre_manager->scene_mgr->getRootSceneNode()->createChildSceneNode();
    scene_node->attachObject(entity);
  } catch(Ogre::Exception &evt) {
    std::cerr << "Mesh Component: " <<  evt.what() << std::endl;
  }
}

int Mesh::get_lua_ref(lua_State * L)
{
  lua_newtable(L);
  return luaL_ref(L, LUA_REGISTRYINDEX);
}

void Mesh::update_from_lua(lua_State * L)
{

}
