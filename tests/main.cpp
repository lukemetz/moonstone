#include <gtest/gtest.h>
#include "utils.hpp"

Ogre_Manager * ogre_manager = 0;

int main(int argc, char **argv)
{
  ogre_manager = new Ogre_Manager(NULL);
  ogre_manager->init();
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
