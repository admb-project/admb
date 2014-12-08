#include <string>
#include <sstream>
#include <gtest/gtest.h>
#include <fvar.hpp>


class test_line_adstring: public ::testing::Test {};

TEST_F(test_line_adstring, istreamoperator)
{
  std::string expected = "kdjfk";
  std::istringstream iss(expected + "\n");

  line_adstring actual;

  iss >> actual;

  ASSERT_STREQ(expected.c_str(), actual);
}
