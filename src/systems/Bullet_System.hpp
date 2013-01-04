#include "System.hpp"
#include "Bullet_Manager.hpp"

struct Bullet_System : public System
{
  void init();
  void update(float dt);
  Bullet_Manager * bullet_manager;
};
