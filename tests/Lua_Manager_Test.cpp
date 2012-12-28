#include <gtest/gtest.h>
#include "Lua_Manager.hpp"
#include "utils.hpp"

class Lua_Manager_Test : public ::testing::Test
{
protected:

  Lua_Manager * lua_manager;
  lua_State * L;
  virtual void SetUp()
  {
    lua_manager = new Lua_Manager();
    L = lua_manager->get_lua_state();
  }

  virtual void TearDown()
  {
    delete lua_manager;
  }
};


TEST_F(Lua_Manager_Test, Vec3f_to_lua_ref_from_ref)
{
  {
    Vec3f vec(1,2,3);
    int val = lua_manager->to_lua_ref(vec);

    lua_rawgeti(L, LUA_REGISTRYINDEX, val);
    Vec3f out;
    lua_manager->from_lua(out);
    EXPECT_VEC3F_EQ(out, vec);
  }

  {
    Vec3f vec(4,2,1);
    int val = lua_manager->to_lua_ref(vec);

    lua_rawgeti(L, LUA_REGISTRYINDEX, val);
    Vec3f out;
    lua_manager->from_lua(out);
    EXPECT_VEC3F_EQ(out, vec);
  }
}
