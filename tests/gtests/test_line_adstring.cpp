#include <string>
#include <sstream>
#include <gtest/gtest.h>
#include <fvar.hpp>
#include <adstring.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

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
TEST_F(test_line_adstring, errormaxlimit)
{
  ad_exit=&test_ad_exit;

  ofstream ofs("maxlimit.txt");
  for (int i = 0; i <= 1025; ++i)
  {
    ofs << "i";
  }
  ofs.close();

  line_adstring a;

  ifstream ifs("maxlimit.txt");
  ASSERT_ANY_THROW({
    ifs >> a;
  });
  ifs.close();
}
