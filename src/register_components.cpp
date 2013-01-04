#include "register_components.hpp"
#include "Manager.hpp"

#include "components/Transform.hpp"
#include "components/Mesh.hpp"
#include "components/Light.hpp"
#include "components/Lua_Component.hpp"
#include "components/Camera.hpp"
#include "components/Input.hpp"

#include "components/Collider.hpp"
#include "components/Rigid_Body.hpp"

void register_components(Manager * manager)
{
  manager->register_component<Transform>("Transform");
  manager->register_component<Mesh>("Mesh");
  manager->register_component<Light>("Light");
  manager->register_component<Camera>("Camera");
  manager->register_component<Lua_Component>("Lua_Component");
  manager->register_component<Input>("Input");
  manager->register_component<Collider>("Collider");
  manager->register_component<Rigid_Body>("Rigid_Body");
}
