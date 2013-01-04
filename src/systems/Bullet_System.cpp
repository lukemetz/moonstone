#include "Bullet_System.hpp"
#include <iostream>

void Bullet_System::init()
{
  bullet_manager = Bullet_Manager::get_instance();
}

void Bullet_System::update(float dt)
{
  bullet_manager->dynamics_world->stepSimulation(dt);
}
