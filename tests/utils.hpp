#pragma once

#define EXPECT_VEC3F_EQ(v1, v2) \
  EXPECT_FLOAT_EQ(vec.x, out.x); \
  EXPECT_FLOAT_EQ(vec.y, out.y); \
  EXPECT_FLOAT_EQ(vec.z, out.z);
