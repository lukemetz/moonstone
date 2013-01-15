#pragma once
#include <string>

class Manager;

struct System
{
  virtual void init() {};
  virtual void update(float dt) {};
  virtual std::string get_name() {return std::string("Generic System");};
  virtual void reload() {};
  virtual void remove() {};
  void set_manager(Manager * manag)
  {
    manager = manag;
  };

protected:
  Manager * manager;
};
