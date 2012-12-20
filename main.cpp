#include <iostream>

#include "utils/Vec3f.hpp"
#include "Manager.hpp"
#include "Transform.hpp"

int main()
{
  Manager *manager = new Manager();
  int index = manager->createEntity();
  Transform *comp = new Transform();
  manager->addComponent(index, comp);
  manager->addComponent(index, comp);
  Vec3f t = Vec3f(1,2,3);
  std::cout << t.x << t.y << t.z << std::endl;
  comp->pos = t;
  comp->rot = Vec3f(1.2, 3.2, 3.3);
  std::vector<int> entities = manager->get_entities(comp->name());
  std::cout << entities.size() << " for " << comp->name() << std::endl;
  return 0;
}
