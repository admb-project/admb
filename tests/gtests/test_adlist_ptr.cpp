#include <gtest/gtest.h>
#include <admodel.h>

class test_adlist_ptr: public ::testing::Test {};

TEST_F(test_adlist_ptr, constructor)
{
  adlist_ptr list(0);
  list.initialize();
}
