#include <btBulletDynamicsCommon.h>

class Bullet_Manager
{
public:
  Bullet_Manager();
  ~Bullet_Manager();


  btBroadphaseInterface * broadphase;
  btDefaultCollisionConfiguration * collision_configuration;
  btCollisionDispatcher * dispatcher;
  btSequentialImpulseConstraintSolver * solver;

  btDiscreteDynamicsWorld * dynamics_world;


};
