#include "Ogre_Render_System.hpp"
#include "Manager.hpp"
#include "components/Transform.hpp"
void Ogre_Render_System::init()
{
  std::vector<int> entities = manager->get_entities("Camera");
  if (entities.size() != 1) {
    std::cerr << "Wrong number of cameras" << std::endl;
    exit(1);
  }

}

void Ogre_Render_System::update(float dt)
{
  std::vector<int> entities = manager->get_entities("Camera");
  if (entities.size() != 1) {
    std::cerr << "Wrong number of cameras" << std::endl;

  } else {
    int entity = entities[0];
    Transform * transform = (Transform*)manager->get_component(entity, "Transform");
    ogre_manager->camera->setPosition(transform->pos.x, transform->pos.y, transform->pos.z);
  }
}
