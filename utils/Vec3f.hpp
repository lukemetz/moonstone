#pragma once
class Vec3f
{
public:
  float x, y, z;

  Vec3f()
  {
    x = y = z = 0;
  }

  Vec3f(float x, float y, float z)
  {
    this->x = x;
    this->y = y;
    this->z = z;
  }
};
