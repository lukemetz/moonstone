#pragma once

#include <vector>
#include <map>
#include "Component.hpp"
#include "System.hpp"

class Manager
{
public:
  Manager();
  int createEntity();
  void add_component(int index, Component *component);
  std::vector<int> get_entities(std::string name);

  void add_system(System * system);
  void update(float dt);

  std::vector<int> get_entities(std::vector<std::string> components);

  Component * get_component(int entity, std::string component_name);
private:
  std::multimap<std::string, int> component_lookup;
  std::map<int, std::map<std::string, Component *>> entity_lookup;
  std::vector<System *> systems;
  int on_entity;

};
