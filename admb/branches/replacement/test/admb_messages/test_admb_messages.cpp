#include <gtest/gtest.h>
#include "admb_messages.h"

class test_admb_messages: public ::testing::Test {};

TEST_F(test_admb_messages, test1)
{
  //FAIL();
  SUCCEED();
}
TEST_F(test_admb_messages, test2)
{
  const adstring expected = "Error: Array bound error in TestBody test valid range is 3 to 4; you had 5";
  adstring m = admb::messages::error_array_bounds(__func__, "test", 3, 4, 5, 0);
  if (m == expected)
  {
    SUCCEED();
  }
  else
  {
    FAIL();
  }
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
