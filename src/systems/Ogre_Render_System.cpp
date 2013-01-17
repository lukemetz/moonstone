#include "Ogre_Render_System.hpp"
#include "Manager.hpp"
#include "components/Transform.hpp"
#include "components/Mesh.hpp"
#include "components/Camera.hpp"
#include "components/Light.hpp"

void Ogre_Render_System::init()
{
  ogre_manager = Ogre_Manager::get_instance();

}

void Ogre_Render_System::update(float dt)
{
  std::vector<int> entities = manager->get_entities("Camera");
  if (entities.size() != 1) {
    std::cerr << "Wrong number of cameras" << std::endl;
    exit(1);
  } else {
    int entity = entities[0];
    Transform * transform = static_cast<Transform*>(manager->get_component(entity, "Transform"));
    Camera * camera = static_cast<Camera*>(manager->get_component(entity, "Camera"));
    ogre_manager->camera->setNearClipDistance(camera->near_clip);//camera->near_clip);
    if (transform) {
      ogre_manager->camera->setPosition(transform->pos.x, transform->pos.y, transform->pos.z);
    }
  }
  std::string types[] = {"Transform", "Mesh"};
  std::vector<std::string> mesh_types(types, types+sizeof(types));
  entities = manager->get_entities(mesh_types);

  for (int entity : entities) {
    Transform * transform = (Transform *) manager->get_component(entity, "Transform");
    Mesh * mesh = (Mesh *) manager->get_component(entity, "Mesh");
    mesh->scene_node->setPosition(transform->pos.x, transform->pos.y, transform->pos.z);
    mesh->scene_node->setOrientation(transform->rot.w, transform->rot.x, transform->rot.y, transform->rot.z);
    mesh->scene_node->setScale(transform->scale.x, transform->scale.y, transform->scale.z);
  }
  std::string l_types[] = {"Transform", "Light"};
  std::vector<std::string> light_types(l_types, l_types+sizeof(l_types));
  entities = manager->get_entities(light_types);

  for (int entity : entities) {
    Transform * transform = (Transform *) manager->get_component(entity, "Transform");
    Light * light = (Light *) manager->get_component(entity, "Light");
    light->light->setPosition(transform->pos.x, transform->pos.y, transform->pos.z);
  }
}
