#include "System.hpp"
#include "Bullet_Manager.hpp"

struct Bullet_System : public System
{
  void init();
  void update(float dt);
  virtual std::string get_name() {
    return "Bullet_System";
  }
  Bullet_Manager * bullet_manager;
};
