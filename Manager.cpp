#include "Manager.hpp"
#include <algorithm>

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
  entity_lookup[entity][component->name()] = component;
}

std::vector<int> Manager::get_entities(std::string name)
{
  std::multimap<std::string, int>::iterator iter;
  std::vector<int> pair;
  auto iterPair = component_lookup.equal_range(name);
  for(iter = iterPair.first; iter != iterPair.second; ++iter) {
    pair.push_back(iter->second);
  }
  return pair;
}

std::vector<int> Manager::get_entities(std::vector<std::string> components)
{
  std::vector<int> sum = get_entities(static_cast<std::string>(components[0]));
  std::vector<std::string>::iterator iter;
  for (iter = components.begin()+1; iter != components.end(); ++iter) {
    std::vector<int> output;
    std::vector<int> sub = get_entities(static_cast<std::string>(*iter));
    std::set_intersection(sum.begin(), sum.end(),
                          sub.begin(), sub.end(),
                          std::back_inserter(output));
    sum = output;
  }
  return sum;
}

Component * Manager::get_component(int entity, std::string component_name)
{
  return entity_lookup[entity][component_name];
}

void Manager::add_system(System *system)
{
  systems.push_back(system);
  system->set_manager(this);
}

void Manager::update(float dt)
{
  for (System *system : systems) {
    system->update(dt);
  }
}
