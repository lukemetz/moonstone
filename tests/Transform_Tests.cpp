#include <gtest/gtest.h>
#include "components/Transform.hpp"
#include "utils.hpp"
#include "Lua_Manager.hpp"

class Transform_Test : public ::testing::Test
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

TEST_F(Transform_Test, same_to_and_from_lua)
{
  for (int i=0; i < 2; i++) {
    Transform * t = new Transform();

    Vec3f old_pos = Vec3f(6,7,8);
    Vec3f old_rot = Vec3f(16,17,18);
    Vec3f old_scale = Vec3f(26,27,28);

    t->pos = old_pos;
    t->rot = old_rot;
    t->scale = old_scale;

    int ref = t->get_lua_ref(L);

    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    t->update_from_lua(L);

    EXPECT_VEC3F_EQ(t->pos, old_pos);
    EXPECT_VEC3F_EQ(t->rot, old_rot);
    EXPECT_VEC3F_EQ(t->scale, old_scale);
  }
}

TEST_F(Transform_Test,  lua_change_to_and_from_lua)
{
  for (int i=0; i < 2; i++) {
    Transform * t = new Transform();

    Vec3f old_pos = Vec3f(6,7,8);
    Vec3f old_rot = Vec3f(16,17,18);
    Vec3f old_scale = Vec3f(26,27,28);

    t->pos = old_pos;
    t->rot = old_rot;
    t->scale = old_scale;

    int ref = t->get_lua_ref(L);

    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);

    lua_getfield(L, -1, "pos");
    lua_pushnumber(L, 123);
    lua_setfield(L, -2, "x");
    lua_pop(L, 1);

    lua_getfield(L, -1, "rot");
    lua_pushnumber(L, 333);
    lua_setfield(L, -2, "y");
    lua_pop(L, 1);

    t->update_from_lua(L);

    EXPECT_VEC3F_EQ(t->pos, Vec3f(123, 7, 8));
    EXPECT_VEC3F_EQ(t->rot, Vec3f(16, 333, 18));
    EXPECT_VEC3F_EQ(t->scale, old_scale);
  }
}

TEST_F(Transform_Test,  c_change_to_and_from_lua)
{
  for (int i=0; i < 2; i++) {
    Transform * t = new Transform();

    Vec3f old_pos = Vec3f(6,7,8);
    Vec3f old_rot = Vec3f(16,17,18);
    Vec3f old_scale = Vec3f(26,27,28);

    t->pos = old_pos;
    t->rot = old_rot;
    t->scale = old_scale;

    int ref = t->get_lua_ref(L);

    //should ignore these changes
    t->pos.x = 12345;
    t->pos.y = 123;
    t->scale.z = 214;

    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);

    t->update_from_lua(L);

    EXPECT_VEC3F_EQ(t->pos, old_pos)
    EXPECT_VEC3F_EQ(t->rot, old_rot);
    EXPECT_VEC3F_EQ(t->scale, old_scale);
  }
}
