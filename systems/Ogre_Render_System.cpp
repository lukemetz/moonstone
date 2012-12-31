#include "Ogre_Render_System.hpp"
#include "Manager.hpp"
#include "components/Transform.hpp"
#include "components/Mesh.hpp"

void Ogre_Render_System::init()
{
  std::vector<int> entities = manager->get_entities("Camera");
  if (entities.size() != 1) {
    std::cerr << "Wrong number of cameras" << std::endl;
    exit(1);
  }

  ogre_manager = Ogre_Manager::get_instance();

}

void Ogre_Render_System::update(float dt)
{
  std::vector<int> entities = manager->get_entities("Camera");
  if (entities.size() != 1) {
    std::cerr << "Wrong number of cameras" << std::endl;

  } else {
    int entity = entities[0];
    Transform * transform = (Transform*)manager->get_component(entity, "Transform");
    if (transform) {
      ogre_manager->camera->setPosition(transform->pos.x, transform->pos.y, transform->pos.z);
    }
  }

  std::vector<std::string> mesh_types = {"Transform", "Mesh"};
  entities = manager->get_entities(mesh_types);

  for (int entity : entities) {
    Transform * transform = (Transform *) manager->get_component(entity, "Transform");
    Mesh * mesh = (Mesh *) manager->get_component(entity, "Mesh");
    mesh->scene_node->setPosition(transform->pos.x, transform->pos.y, transform->pos.z);
    mesh->scene_node->setScale(transform->scale.x, transform->scale.y, transform->scale.z);
  }
}
