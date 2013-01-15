#include "Bullet_Manager.hpp"

Bullet_Manager * Bullet_Manager::instance = nullptr;

Bullet_Manager::Bullet_Manager()
{
  broadphase = new btDbvtBroadphase();
  collision_configuration = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collision_configuration);
  solver = new btSequentialImpulseConstraintSolver();

  dynamics_world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collision_configuration);
  dynamics_world->setGravity(btVector3(0, -9.81, 0));
  instance = this;
}

Bullet_Manager::~Bullet_Manager()
{
  delete dynamics_world;
  delete solver;
  delete dispatcher;
  delete collision_configuration;
  delete broadphase;
}

Bullet_Manager * Bullet_Manager::get_instance()
{
  return instance;
}

void Bullet_Manager::add_rigid_body(btRigidBody * body)
{
  dynamics_world->addRigidBody(body);
}

void Bullet_Manager::remove_rigid_body(btRigidBody * body)
{
  dynamics_world->removeRigidBody(body);
}
