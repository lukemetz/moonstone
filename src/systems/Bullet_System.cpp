#include "Bullet_System.hpp"

#include "components/Rigid_Body.hpp"
#include "components/Transform.hpp"
#include "Manager.hpp"
#include <vector>
#include <iostream>

void Bullet_System::init()
{
  bullet_manager = Bullet_Manager::get_instance();
}

void Bullet_System::update(float dt)
{

  std::string types[] = {"Rigid_Body", "Transform"};
  std::vector<std::string> mesh_types(types, types+2);

  auto entities = manager->get_entities(mesh_types);
  for (int entity : entities) {
    Transform * t = static_cast<Transform *> (manager->get_component(entity, std::string("Transform")));
    Rigid_Body * r = static_cast<Rigid_Body *> (manager->get_component(entity, std::string("Rigid_Body")));
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
    r->body->setLinearVelocity(btVector3(r->velocity.x, r->velocity.y, r->velocity.z));

    //update the rigid body
    r->body->clearForces();
    r->body->applyCentralForce(btVector3(r->forces.x, r->forces.y, r->forces.z));

    r->body->applyTorque(btVector3(r->torque.x, r->torque.y, r->torque.z));
    
    r->body->setFriction(r->friction);

    r->body->setAngularVelocity(btVector3(r->angular_velocity.x, r->angular_velocity.y, r->angular_velocity.z));
    
    r->body->setAngularFactor(btVector3(
          r->angular_factor.x,
          r->angular_factor.y,
          r->angular_factor.z ));

    r->body->setLinearFactor(btVector3(
          r->linear_factor.x,
          r->linear_factor.y,
          r->linear_factor.z ));
  }

  bullet_manager->dynamics_world->stepSimulation(dt);
  for (int entity : entities) {
    Transform * t = static_cast<Transform *> (manager->get_component(entity, std::string("Transform")));
    Rigid_Body * r = static_cast<Rigid_Body *> (manager->get_component(entity, std::string("Rigid_Body")));
    btVector3 vel = r->body->getLinearVelocity();
    r->velocity = Vec3f(vel.getX(), vel.getY(), vel.getZ());

    btVector3 angular_vel = r->body->getAngularVelocity();
    r->angular_velocity = Vec3f(angular_vel.getX(), angular_vel.getY(), angular_vel.getZ());

  }
}
