#pragma once

#include <string>

struct Component
{
  virtual std::string name() {return "Hello";};
};

