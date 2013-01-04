#pragma once
#include <btBulletDynamicsCommon.h>
class Bullet_Manager;
class Bullet_Manager
{
public:
  Bullet_Manager();
  ~Bullet_Manager();

  void add_rigid_body(btRigidBody * body);

  btBroadphaseInterface * broadphase;
  btDefaultCollisionConfiguration * collision_configuration;
  btCollisionDispatcher * dispatcher;
  btSequentialImpulseConstraintSolver * solver;

  btDiscreteDynamicsWorld * dynamics_world;

  static Bullet_Manager * instance;
  static Bullet_Manager * get_instance();
};
