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

  std::vector<std::string> mesh_types = {"Rigid_Body", "Transform"};
  auto entities = manager->get_entities(mesh_types);
  for (int entity : entities) {
    Transform * t = static_cast<Transform *> (manager->get_component(entity, "Transform"));
    Rigid_Body * r = static_cast<Rigid_Body *> (manager->get_component(entity, "Rigid_Body"));
    if (r->on_step == 0) {
      //Set the initial pos
      btTransform trans;
      trans.setIdentity();
      trans.setOrigin(btVector3(t->pos.x, t->pos.y, t->pos.z));
      trans.setRotation(btQuaternion(t->rot.x, t->rot.y, t->rot.z, t->rot.w));
      btMotionState * motion_state = r->body->getMotionState();
      motion_state->setWorldTransform(trans);

      r->body->setMotionState(motion_state);
      r->on_step += 1;
    }
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

  bullet_manager->dynamics_world->stepSimulation(dt);
}
