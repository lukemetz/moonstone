#pragma once

#include "System.hpp"

struct OIS_Input_System : public System
{
  OIS_Input_System();
  ~OIS_Input_System();
  void init();
  void update(float dt);
  virtual std::string get_name() {
    return "OIS_Input_System";
  }
  bool *keys;
  bool *mouse;
  int *mouse_dx;
  int *mouse_dy;
protected:
  int input_ref;
  void update_lua();
};
