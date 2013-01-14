#pragma once
#include <string>

class Manager;

struct System
{
  virtual void init() {};
  virtual void update(float dt) {};
  virtual std::string get_name() {return "Generic System";};

  void set_manager(Manager * manag)
  {
    manager = manag;
  };

protected:
  Manager * manager;
};
