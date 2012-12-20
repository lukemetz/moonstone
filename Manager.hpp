#include <vector>
#include <map>
#include "Component.hpp"
class Manager
{
public:
  Manager();
  int createEntity();
  void addComponent(int index, Component *component);
  std::vector<int> get_entities(std::string name);

private:
  std::multimap<std::string, int> component_lookup;
  std::map<int, std::vector<Component *>> entity_lookup;
  int on_entity;
};
