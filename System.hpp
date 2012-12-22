#pragma once

class Manager;

struct System
{
  virtual void init() {};
  virtual void update(float dt) {};

  void set_manager(Manager * manag)
  {
    manager = manag;
  };

private:
  Manager * manager;
};
