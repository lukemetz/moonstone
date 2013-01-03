#include "Bullet_Manager.hpp"

Bullet_Manager::Bullet_Manager()
{
  broadphase = new btDbvtBroadphase();
  collision_configuration = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collision_configuration);
  solver = new btSequentialImpulseConstraintSolver();

  dynamics_world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collision_configuration);
  dynamics_world->setGravity(btVector3(0, -9.81, 0));
}

Bullet_Manager::~Bullet_Manager()
{
  delete dynamics_world;
  delete solver;
  delete dispatcher;
  delete collision_configuration;
  delete broadphase;
}
