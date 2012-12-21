#include "Manager.hpp"

Manager::Manager()
{
  on_entity = 0;
}

int Manager::createEntity()
{
  return on_entity++;
}

void Manager::add_component(int entity, Component *component)
{
  component_lookup.insert(std::pair<std::string, int>(component->name(), entity));
  entity_lookup[entity].push_back(component);
}

std::vector<int> Manager::get_entities(std::string name)
{
  std::multimap<std::string, int>::iterator iter;
  std::vector<int> pair;
  auto iterPair = component_lookup.equal_range(name);
  //for (auto pair : iterPair) {
  for(iter = iterPair.first; iter != iterPair.second; ++iter) {
    pair.push_back(iter->second);
  }
  return pair;
}

void Manager::add_system(System *system)
{
  systems.push_back(system);
}

void Manager::update(float dt)
{
  for (System *system : systems) {
    system->update(dt);
  }
}
