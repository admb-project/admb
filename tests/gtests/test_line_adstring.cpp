#include <string>
#include <sstream>
#include <gtest/gtest.h>
#include <fvar.hpp>
#include <adstring.hpp>


class test_line_adstring: public ::testing::Test {};

TEST_F(test_line_adstring, istreamoperator)
{
  std::string expected = "kdjfk";
  std::istringstream iss(expected + "\n");

  line_adstring actual;

  iss >> actual;

  ASSERT_STREQ(expected.c_str(), actual);
}
TEST_F(test_line_adstring, assignment_adstring)
{
  adstring expected = "kdjfk";

  line_adstring actual;

  actual = expected;

  ASSERT_STREQ(expected, actual);
}
TEST_F(test_line_adstring, assignment_char)
{
  const char* expected = "kdjfk";

  line_adstring actual;

  actual = expected;

  ASSERT_STREQ(expected, actual);
}
