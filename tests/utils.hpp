#pragma once

#define EXPECT_VEC3F_EQ(v1, v2) \
  EXPECT_FLOAT_EQ(v1.x, v2.x); \
  EXPECT_FLOAT_EQ(v1.y, v2.y); \
  EXPECT_FLOAT_EQ(v1.z, v2.z);
