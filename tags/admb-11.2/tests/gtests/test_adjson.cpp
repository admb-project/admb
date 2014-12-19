#include <gtest/gtest.h>
#include "adjson.h"

class test_adjson: public ::testing::Test {};

TEST_F(test_adjson, constructor)
{
  adjson::object o;
}
