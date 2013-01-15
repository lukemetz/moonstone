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

  names.clear();

  //setup with empty strings
  int n = entity->getNumSubEntities();
  for(int i=0; i < n; ++i) {
    names.push_back("");
  }

  auto map = entity->getMesh()->getSubMeshNameMap();
  for(auto iter = map.begin(); iter != map.end(); ++iter) {
    Ogre::String key = iter->first;
    int value = iter->second;
    names[value] = key;
  }
}

void Mesh::remove()
{
  Ogre_Manager * ogre_manager = Ogre_Manager::get_instance();
  ogre_manager->scene_mgr->destroyEntity(entity);
  ogre_manager->scene_mgr->destroySceneNode(scene_node);
  entity = nullptr;
  scene_node = nullptr;
}

int Mesh::get_lua_ref(lua_State * L)
{
  lua_newtable(L);

  int n = entity->getNumSubEntities();
  for(int i=0; i < n; ++i) {
    Ogre::SubEntity * s = entity->getSubEntity(i);
    lua_newtable(L);
      lua_pushstring(L, s->getMaterialName().c_str());
      lua_setfield(L, -2, "material");
      lua_pushstring(L, names[i].c_str());
      lua_setfield(L, -2, "name");
    if (names[i] != "") {
      lua_pushvalue(L, -2);
      lua_setfield(L, -3, names[i].c_str());
    }
    lua_rawseti(L, -2, i);
  }

  return luaL_ref(L, LUA_REGISTRYINDEX);
}

void Mesh::update_from_lua(lua_State * L)
{

}

void Mesh::init_from_lua(lua_State * L)
{
  lua_getfield(L, -1, "filename");
  if(lua_isnil(L, -1)) {
    std::cerr << "No filename specified for mesh from lua" << std::endl;
    exit(1);
  }
  std::string filename(lua_tostring(L, -1));
  set_file(filename);
  lua_pop(L, 1);
}
