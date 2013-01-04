#include "Bullet_System.hpp"

#include "components/Rigid_Body.hpp"
#include "components/Transform.hpp"
#include "Manager.hpp"

#include <vector>

void Bullet_System::init()
{
  bullet_manager = Bullet_Manager::get_instance();
}

void Bullet_System::update(float dt)
{
  bullet_manager->dynamics_world->stepSimulation(dt);

  std::vector<std::string> mesh_types = {"Rigid_Body", "Transform"};
  auto entities = manager->get_entities(mesh_types);
  for (int entity : entities) {
    Transform * t = static_cast<Transform *> (manager->get_component(entity, "Transform"));
    Rigid_Body * r = static_cast<Rigid_Body *> (manager->get_component(entity, "Rigid_Body"));
    btTransform trans;
    r->body->getMotionState()->getWorldTransform(trans);

    t->pos = Vec3f(trans.getOrigin().getX(),
                   trans.getOrigin().getY(),
                   trans.getOrigin().getZ());

    t->rot = Quat(trans.getRotation().getX(),
                   trans.getRotation().getY(),
                   trans.getRotation().getZ(),
                   trans.getRotation().getW());
  }
}
