#include "Manager.hpp"
#include <algorithm>
#include <iostream>
#include "Lua_Manager.hpp"
#include "systems/Lua_System.hpp"
#include "components/Lua_Component.hpp"
#include <sstream>
#include "init_from_lua.hpp"

Manager::Manager()
{
  on_entity = 1; //Lua based start at 1
}

int Manager::createEntity()
{
  entities.push_back(on_entity);
  return on_entity++;
}

void Manager::add_component(int entity, Component *component)
{
  component_lookup.insert(std::pair<std::string, int>(component->name(), entity));
  entity_lookup[entity][component->name()] = component;
  component->added_to_entity(this, entity);
}

void Manager::set_prefix(std::string path)
{
  prefix = path;
}

Component * Manager::create_component(std::string name)
{
  auto iter = string_component_lookup.find(name);
  if (iter != string_component_lookup.end()) {
    return string_component_lookup[name]();
  } else {
    //Look in the lua directory and make from there.
    Lua_Component * c = (Lua_Component *)string_component_lookup["Lua_Component"]();
    std::stringstream ss;
    c->set_name(name);
    return c;
  }
}

System* Manager::create_system(std::string name)
{
  auto iter = string_system_lookup.find(name);
  if (iter != string_system_lookup.end()) {
    return string_system_lookup[name]();
  } else {
    //Look in the lua directory and make from there.
    Lua_System * s = (Lua_System *) string_system_lookup["Lua_System"]();
    std::stringstream ss;
    ss << prefix << "/systems/" << name << ".lua";
    std::string filename = ss.str();
    std::cout << "Component from: " << filename << std::endl;
    s->set_file(filename);
    s->set_name(name);
    return s;
  }
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
  std::vector<int> empty;
  if (components.size() == 0) {
    return empty;
  }

  //start with first component
  std::vector<int> sum = get_entities(static_cast<std::string>(components[0]));
  std::vector<std::string>::iterator iter;
  //keep subtracting away
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
std::vector<int> Manager::get_all_entities()
{
  return entities;
}

std::map<std::string, Component *> Manager::get_all_components_map(int entity)
{
  return entity_lookup[entity];
}

Component * Manager::get_component(int entity, std::string component_name)
{
  auto iter = entity_lookup[entity].find(component_name);
  if ( iter == entity_lookup[entity].end() ) {
    return nullptr;
  }
  return iter->second;
}

void Manager::add_system(System *system)
{
  systems.push_back(system);
  system->set_manager(this);
  system->init();
}

void Manager::update(float dt)
{

  for (System *system : systems) {
    //pause all but input and pause systems
    if (paused == true &&
        (system->get_name() != "OIS_Input_System" &&
         system->get_name() != "Pause_System")) {
      continue;
    }
    system->update(dt);
  }
}
void Manager::pause()
{
  paused = true;
}

void Manager::resume()
{
  paused = false;
  for (System * system : systems) {
    system->reload();
  }
void Manager::create_entities_from_file()
{
  //This function is awful......
  int old_file_entities = init_from_lua(this, entities_file);
  set_original_entities_ref(old_file_entities);
}
