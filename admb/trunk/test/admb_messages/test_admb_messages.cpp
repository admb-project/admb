#include <gtest/gtest.h>
#include "admb_messages.h"

class test_admb_messages: public ::testing::Test {};

TEST_F(test_admb_messages, test1)
{
  FAIL();
}
TEST_F(test_admb_messages, test2)
{
  SUCCEED();
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  //admb::messages::outofbounds();
  return RUN_ALL_TESTS();
}
