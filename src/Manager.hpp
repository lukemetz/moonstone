#pragma once

#include <vector>
#include <map>
#include "Component.hpp"
#include "System.hpp"

template<typename T> T* create_inst()
{
  return new T();
};

class Manager
{
public:
  Manager();
  int createEntity();
  void add_component(int index, Component *component);
  Component * create_component(std::string);
  std::vector<int> get_entities(std::vector<std::string> components);
  Component * get_component(int entity, std::string component_name);
  std::vector<int> get_entities(std::string name);
  template<typename T> void register_component(std::string name)
  {
    string_component_lookup[name] = (Component *(*)())&create_inst<T>;
  }

  template<typename T> void register_system(std::string name)
  {
    string_system_lookup[name] = (System *(*)()) &create_inst<T>;
  }
  System* create_system(std::string name);

  void add_system(System * system);
  void update(float dt);

  void set_prefix(std::string path);

protected:
  std::map<std::string, Component*(*)()> string_component_lookup;
  std::multimap<std::string, int> component_lookup;
  std::map<int, std::map<std::string, Component *>> entity_lookup;
  std::vector<System *> systems;
  std::map<std::string, System*(*)()> string_system_lookup;
  int on_entity;
  std::string prefix;

};
