#pragma once
class Quat
{
public:
  float x, y, z, w;

  Quat()
  {
    x = y = z = 0;
    w = 1;
  }
  Quat(float x, float y, float z, float w)
  {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
  }
};
