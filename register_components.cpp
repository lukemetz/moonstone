#include "register_components.hpp"
#include "Manager.hpp"

#include "components/Transform.hpp"
#include "components/Mesh.hpp"
#include "components/Lua_Component.hpp"
#include "components/Camera.hpp"

void register_components(Manager * manager)
{
  manager->register_component<Transform>("Transform");
  manager->register_component<Mesh>("Mesh");
  manager->register_component<Camera>("Camera");
  manager->register_component<Lua_Component>("Lua_Component");
}
