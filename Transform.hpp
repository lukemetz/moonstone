#pragma once

#include "Component.hpp"
#include <utils/Vec3f.hpp>
struct Transform : public Component
{
  Vec3f pos;
  Vec3f rot;
  Vec3f scale;
  virtual std::string name() { return "Transform"; };
};
