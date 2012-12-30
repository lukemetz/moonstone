#include "Mesh.hpp"

Mesh::Mesh()
{
  entity = 0;
  scene_node = 0;
}

void Mesh::set_file(std::string filename)
{
  entity = nullptr;
  scene_node = nullptr;
  Ogre_Manager * ogre_manager = Ogre_Manager::get_instance();

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

void Mesh::init_from_lua(lua_State * L)
{
  lua_getfield(L, -1, "filename");
  std::string filename(lua_tolstring(L, -1, NULL));
  set_file(filename);
  lua_pop(L, 1);
}
